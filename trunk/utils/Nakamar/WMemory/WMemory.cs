using System;
using System.Diagnostics;
using System.Windows.Input;
using Magic;
using Util;
using WLibrary;

namespace WoWMemoryManager
{
    public class MemoryManager
    {
        public RawMemoryManager memoryManager;
        public KeyBoard KeyBoard;

        private BlackMagic BM;
        private PatternFinder patternFinder;
        public GameMonitor gameMonitor { get; private set; }

        private static EquatableList<double> signature = new EquatableList<double>(901791, 349667, 371721, 139443, 213674);
        private AddonSignatureManager addonSignatureManager;
        private AddonMessage LastMessage;
        private int LastProcessedMessage = -1;

        public ObjectManager ObjectManager
        {
            get
            {
                return new ObjectManager(memoryManager, patternFinder, gameMonitor.pObjectManager);
            }
        }

        private void Log(string message)
        {
            Logger.Log(this.GetType().Name, message);
        }

        private void LogError(string message)
        {
            Logger.LogError(this.GetType().Name, message);
        }

        private uint FindPattern(Pattern pattern)
        {
            return patternFinder.FindPattern(pattern);
        }

        public MemoryManager(int id)
        {
            BM = new BlackMagic(id);
            memoryManager = new BlackMagicAdapter(BM);
            KeyBoard = new KeyBoard(BM.WindowHandle);
            patternFinder = new CachingPatternFinder(memoryManager, message => Logger.Log(typeof(CachingPatternFinder).Name, message));
            gameMonitor = new GameMonitorImpl(memoryManager, patternFinder, message => Logger.LogError(typeof(GameMonitorImpl).Name, message));
            addonSignatureManager = new AddonSignatureManagerImpl(memoryManager, message => Logger.Log(typeof(AddonSignatureManagerImpl).Name, message));
            LastMessage = null;
        }

        /// <summary>
        /// возвращает тру если окно WoW сейчас активно
        /// </summary>
        /// <returns></returns>
        public bool IsWoWForeground()
        {
            return BM.WindowHandle == Extern.GetForegroundWindow();
        }

        public void ActivateWoWWindow()
        {
            Extern.ShowWindow(BM.WindowHandle, WindowShowStyle.ShowNormal);
            Extern.SetForegroundWindow(BM.WindowHandle);
        }

        public void WaitForInputIdle()
        {
            // такая штука тоже часто срабатывает раньше времени
            Process.GetProcessById(BM.ProcessId).WaitForInputIdle();
            TimeSpan responseTime;
            do
            {
                DateTime before = DateTime.Now;
                KeyBoard.PressKey(Key.LeftCtrl, true);
                responseTime = DateTime.Now - before;
            }
            while (responseTime.TotalSeconds > 1);
        }

        public void StopWoW()
        {
            Log("Закрываю WoW...");
            Process wow = Process.GetProcessById(BM.ProcessId);
            wow.CloseMainWindow();
            wow.WaitForExit();
            Log("WoW закрыт");
        }

        private uint min(uint x, uint y)
        {
            return x < y ? x : y;
        }

        private string[] GetRawAddonMessage(EquatableList<double> signature)
        {
            uint p = addonSignatureManager.Cached(signature);
            if (p == 0)
            {
                return null;
            }

            try
            {
                uint pMessage = memoryManager.ReadUInt(p + 16 * (uint)signature.Count);
                uint pTarget = memoryManager.ReadUInt(p + 16 * ((uint)signature.Count + 1));
                uint pDoNotRestart = memoryManager.ReadUInt(p + 16 * ((uint)signature.Count + 2));
                uint pNeedPurchaseConfirmation = memoryManager.ReadUInt(p + 16 * ((uint)signature.Count + 3));
                uint pCurrentState = memoryManager.ReadUInt(p + 16 * ((uint)signature.Count + 4));
                uint pNothingToDo = memoryManager.ReadUInt(p + 16 * ((uint)signature.Count + 5));
                uint pGuildStats = memoryManager.ReadUInt(p + 16 * ((uint)signature.Count + 6));
                uint pDoneEverything = memoryManager.ReadUInt(p + 16 * ((uint)signature.Count + 7));

                // http://www.mmowned.com/forums/wow-memory-editing/108898-memory-reading-chat-w-help-add.html#post717199
                const uint limit = 1000000;
                string text = memoryManager.ReadUTF8String(pMessage + 0x14, Math.Min(limit, memoryManager.ReadUInt(pMessage + 0x10)));
                string target = memoryManager.ReadUTF8String(pTarget + 0x14, Math.Min(limit, memoryManager.ReadUInt(pTarget + 0x10)));
                string DoNotRestart = memoryManager.ReadUTF8String(pDoNotRestart + 0x14, Math.Min(limit, memoryManager.ReadUInt(pDoNotRestart + 0x10)));
                string NeedPurchaseConfirmation =
                    memoryManager.ReadUTF8String(pNeedPurchaseConfirmation + 0x14, Math.Min(limit, memoryManager.ReadUInt(pNeedPurchaseConfirmation + 0x10)));
                string CurrentState = memoryManager.ReadUTF8String(pCurrentState + 0x14, Math.Min(limit, memoryManager.ReadUInt(pCurrentState + 0x10)));
                string NothingToDo = memoryManager.ReadUTF8String(pNothingToDo + 0x14, Math.Min(limit, memoryManager.ReadUInt(pNothingToDo + 0x10)));
                string GuildStats = memoryManager.ReadUTF8String(pGuildStats + 0x14, Math.Min(limit, memoryManager.ReadUInt(pGuildStats + 0x10)));
                string DoneEverything = memoryManager.ReadUTF8String(pDoneEverything + 0x14, Math.Min(limit, memoryManager.ReadUInt(pDoneEverything + 0x10)));

                // если будут частые чтения неконсистентных данных
                // (ведь синхронизации с WoW никакой нет, а запись строки со стороны аддона не атомарна)
                // то сделать тут какую-нибудь контрольную сумму по каждому из читаемых полей
                // в аддоне её считать, а тут - проверять

                // также если встроенная в WoW машина Lua будет часто перемещать массив с места на место,
                // то мы можем напороться на устаревшую копию массива -
                // этому можно противодействовать введением времени в сигнатуру

                return new string[] { text, target, DoNotRestart, NeedPurchaseConfirmation, CurrentState, NothingToDo, GuildStats, DoneEverything };
            }
            catch (Exception ex)
            {
                Log(string.Format("Не удалось прочитать сообщение от аддона ({0}). Очищаю кэш", ex.Message));
                Log(ex.ToString());
                addonSignatureManager.ClearCache();
                return null;
            }
        }

        public AddonMessage GetAddonMessage()
        {
            return GetAddonMessage(true);
        }

        /// <summary>
        /// id|command;arg1;arg2;...
        /// </summary>
        /// <returns></returns>
        public AddonMessage GetAddonMessage(bool lastIfPatternFailed)
        {
            string[] raw = GetRawAddonMessage(signature);
            if (raw == null)
                return lastIfPatternFailed ? LastMessage : null;
            string text = raw[0];
            string target = raw[1];
            string DoNotRestart = raw[2];
            string[] ss = text.Split('|');

            AddonMessage result = new AddonMessage();
            result.Id = int.Parse(ss[0]);
            string[] tt = ss[1].Split(';');
            result.Command = tt[0];
            result.Arguments = new string[tt.Length-1];
            Array.Copy(tt, 1, result.Arguments, 0, tt.Length-1);
            result.Target = target;
            result.DoNotRestart = DoNotRestart;
            result.NeedPurchaseConfirmation = !String.IsNullOrEmpty(raw[3]);
            result.CurrentState = raw[4];
            result.NothingToDo = raw[5] == "yes";

            result.guildBank = String.IsNullOrEmpty(raw[6]) ? null : new GuildBankInfo(raw[6]);

            result.doneEverything = !String.IsNullOrEmpty(raw[7]);

            return LastMessage = result;
        }

        public AddonMessage RescanAddonMessage()
        {
            addonSignatureManager.Search(signature);
            return GetAddonMessage(false);
        }

        public bool NewAddonMessage()
        {
            return GetAddonMessage() != null && GetAddonMessage().Id > LastProcessedMessage;
        }

        public void ProcessAddonMessage(int id)
        {
            LastProcessedMessage = id;
        }

        public string TargetName
        {
            get
            {
                return GetAddonMessage() == null ? null : GetAddonMessage().Target;
            }
        }

        public GameState CurrentGameState { get { return gameMonitor.CurrentGameState; } }

        public IntPtr WoWWindowHandle { get { return BM.WindowHandle; } }
    }
}
