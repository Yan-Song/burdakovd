using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Windows.Input;
using Magic;
using Util;
using WLibrary;

namespace WoWMemoryManager
{
    /// <summary>
    /// Класс-переросток =(
    /// </summary>
    public class MemoryManager
    {
        public RawMemoryManager memoryReader;
        public KeyBoard KeyBoard;

        private BlackMagic BM;
        private PatternFinder patternFinder;
        public GameMonitor gameMonitor { get; private set; }

        private Dictionary<ComparableListOfDouble, uint> DynamicDoublePatternCache = new Dictionary<ComparableListOfDouble, uint>();
        private static ComparableListOfDouble signature = new ComparableListOfDouble(901791, 349667, 371721, 139443, 213674);
        private AddonMessage LastMessage;
        private int LastProcessedMessage = -1;

        public ObjectManager ObjectManager
        {
            get
            {
                return new ObjectManager(memoryReader, patternFinder, gameMonitor.pObjectManager);
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
            memoryReader = new BlackMagicAdapter(BM);
            KeyBoard = new KeyBoard(BM.WindowHandle);
            patternFinder = new CachingPatternFinder(memoryReader, delegate(string message) { Logger.Log(typeof(CachingPatternFinder).Name, message); });
            gameMonitor = new GameMonitorImpl(memoryReader, patternFinder);
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

        private uint CachedDoublePattern(ComparableListOfDouble pattern)
        {
            if (DynamicDoublePatternCache.ContainsKey(pattern))
            {
                uint cached = DynamicDoublePatternCache[pattern];
                bool ok = true;
                
                try
                {
                    if (!CheckDoublePattern(DynamicDoublePatternCache[pattern], pattern))
                        ok = false;
                }
                catch
                {
                    ok = false;
                }

                if (ok)
                {
                    return cached;
                }
                else
                {
                    DynamicDoublePatternCache.Remove(pattern);
                    Log("Сигнатура аддона потеряна");
                }
            }

            return 0;
        }

        /// <summary>
        /// ищет последовательность double в памяти, учитывая что они располагаются не подряд,
        /// а с промежутком в 8 байт на служебную информацию lua
        /// также учитывает что значения гарантировано находятся по адресу кратному 8
        /// http://www.mmowned.com/forums/wow-memory-editing/108898-memory-reading-chat-w-help-add.html
        /// </summary>
        private uint FindDoublePattern(ComparableListOfDouble pattern)
        {
            uint cached = CachedDoublePattern(pattern);

            if (cached != 0)
                return cached;

            DateTime startTime = DateTime.Now;

            uint bufferSize = 1<<26;

            foreach(MEMORY_BASIC_INFORMATION m in Extern.EnumerateMemoryRanges(BM.ProcessHandle))

                if (m.State == MemoryState.MEM_COMMIT &&
                    m.lType == MemoryType.MEM_PRIVATE &&
                    m.Protect == (uint)ProtectStatus.READWRITE)

                    for (uint start = m.BaseAddress; start < m.BaseAddress + m.RegionSize; start += bufferSize)
                    {
                        uint readBytes = min(bufferSize, m.BaseAddress + m.RegionSize - start);
                        uint pos = FindDoublePattern(start, readBytes, pattern);
                        if (pos != 0)
                        {
                            Log("Сигнатура аддона найдена по адресу 0x" +
                                pos.ToString("X8") + " за " + (DateTime.Now-startTime) + " сек.");
                            DynamicDoublePatternCache[pattern] = pos;
                            return pos;
                        }
                    }
            return 0;
        }

        private uint FindDoublePattern(uint start, uint readBytes, List<double> pattern)
        {
            uint readDoubles = readBytes / 8;

            double[] buffer = ReadDoubles(start, readDoubles);

            if (buffer == null) return 0;

            int finish = (int)readDoubles - pattern.Count;

            for (int i = 0; i < finish; ++i)
            {
                bool ok = true;

                for (int j = 0, p = i; ok && j < pattern.Count; ++j, p += 2)
                    if (pattern[j] != buffer[p])
                        ok = false;

                if (ok)
                    return start + (uint)i * 8;
            }
            return 0;
        }

        private bool CheckDoublePattern(uint start, List<double> pattern)
        {
            return FindDoublePattern(start, (uint)pattern.Count * 16, pattern)==start;
        }

        private double[] ReadDoubles(uint start, uint readDoubles)
        {
            uint readBytes = readDoubles * 8;
            double[] result = new double[readDoubles];
            IntPtr lpBuffer = IntPtr.Zero;

            if(sizeof(byte) * 8 != sizeof(double))
                throw new Exception("o_O");
            
            try
			{
                lpBuffer = Marshal.AllocHGlobal((int)readBytes);

                uint iBytesRead = (uint)SMemory.ReadRawMemory(BM.ProcessHandle, start, lpBuffer, (int)readBytes);
                
                if (iBytesRead != readBytes)
                    throw new Exception("ReadProcessMemory error in ReadDoubles");
		
                Marshal.Copy(lpBuffer, result, 0, result.Length);
			}
			catch
			{
				return null;
			}
			finally
			{
				if (lpBuffer != IntPtr.Zero)
					Marshal.FreeHGlobal(lpBuffer);
			}
            return result;
        }

        private uint min(uint x, uint y)
        {
            return x < y ? x : y;
        }

        private string[] GetRawAddonMessage(ComparableListOfDouble signature)
        {
            uint p = CachedDoublePattern(signature);
            if (p == 0)
            {
                return null;
            }

            try
            {
                uint pMessage = memoryReader.ReadUInt(p + 16 * (uint)signature.Count);
                uint pTarget = memoryReader.ReadUInt(p + 16 * ((uint)signature.Count + 1));
                uint pDoNotRestart = memoryReader.ReadUInt(p + 16 * ((uint)signature.Count + 2));
                uint pNeedPurchaseConfirmation = memoryReader.ReadUInt(p + 16 * ((uint)signature.Count + 3));
                uint pCurrentState = memoryReader.ReadUInt(p + 16 * ((uint)signature.Count + 4));
                uint pNothingToDo = memoryReader.ReadUInt(p + 16 * ((uint)signature.Count + 5));
                uint pGuildStats = memoryReader.ReadUInt(p + 16 * ((uint)signature.Count + 6));

                // http://www.mmowned.com/forums/wow-memory-editing/108898-memory-reading-chat-w-help-add.html#post717199
                const uint limit = 1000000;
                string text = memoryReader.ReadUTF8String(pMessage + 0x14, Math.Min(limit, memoryReader.ReadUInt(pMessage + 0x10)));
                string target = memoryReader.ReadUTF8String(pTarget + 0x14, Math.Min(limit, memoryReader.ReadUInt(pTarget + 0x10)));
                string DoNotRestart = memoryReader.ReadUTF8String(pDoNotRestart + 0x14, Math.Min(limit, memoryReader.ReadUInt(pDoNotRestart + 0x10)));
                string NeedPurchaseConfirmation =
                    memoryReader.ReadUTF8String(pNeedPurchaseConfirmation + 0x14, Math.Min(limit, memoryReader.ReadUInt(pNeedPurchaseConfirmation + 0x10)));
                string CurrentState = memoryReader.ReadUTF8String(pCurrentState + 0x14, Math.Min(limit, memoryReader.ReadUInt(pCurrentState + 0x10)));
                string NothingToDo = memoryReader.ReadUTF8String(pNothingToDo + 0x14, Math.Min(limit, memoryReader.ReadUInt(pNothingToDo + 0x10)));
                string GuildStats = memoryReader.ReadUTF8String(pGuildStats + 0x14, Math.Min(limit, memoryReader.ReadUInt(pGuildStats + 0x10)));

                // если будут частые чтения неконсистентных данных
                // (ведь синхронизации с WoW никакой нет, а запись строки со стороны аддона не атомарна)
                // то сделать тут какую-нибудь контрольную сумму по каждому из читаемых полей
                // в аддоне её считать, а тут - проверять

                // также если встроенная в WoW машина Lua будет часто перемещать массив с места на место,
                // то мы можем напороться на устаревшую копию массива -
                // этому можно противодействовать введением времени в сигнатуру

                return new string[] { text, target, DoNotRestart, NeedPurchaseConfirmation, CurrentState, NothingToDo, GuildStats };
            }
            catch (Exception ex)
            {
                Log(string.Format("Не удалось прочитать сообщение от аддона ({0}). Удаляю кэшированный адрес {1}", ex.Message, p));
                DynamicDoublePatternCache.Remove(signature);
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

            return LastMessage = result;
        }

        public AddonMessage RescanAddonMessage()
        {
            FindDoublePattern(signature);
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
