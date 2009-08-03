using System;
using System.Collections;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Windows.Input;
using Magic;
using Util;
using WoWMemoryManager.WoWObject;
using WoWMemoryManager.Properties;
using System.Collections.Generic;

/*
// вычисляем оффсеты
// 007C0799 - 8b 0d 80 9f 13 01          - mov ecx,[01139f80]
// 007C079F - 89 81 34 2c 00 00          - mov [ecx+00002c34],eax

// [[01139f80] + 00002c34]

// FindPattern(Patterns.ClientConnection) - здесь находится вышеуказанный код, ~007C0799
// WoW.ReadUInt(FindPattern(Patterns.ClientConnection)) - адрес указателя на ClientConnection, 01139f80
// WoW.ReadUInt(WoW.ReadUInt(FindPattern(Patterns.ClientConnection))) указатель на ClientConnection 

uint ppClientConnection = WoW.ReadUInt(WoW.ReadUInt(FindPattern(Patterns.ClientConnection)));         

uint ObjectManagerOffset = WoW.ReadUInt(FindPattern(Patterns.ObjectManagerOffset));

uint pObjectManager = WoW.ReadUInt(pClientConnection + ObjectManagerOffset);
*/


namespace WoWMemoryManager
{
    public enum GameState { None, Login, RealmWizard, Character, World };

    public class AddonMessage
    {
        public int Id;
        public string Command;
        public string[] Arguments;
        public string Target;
        public string DoNotRestart;
        public bool NeedPurchaseConfirmation;

        public override string ToString()
        {
            return "[AddonMessage #" + Id + "]: " + Command + "(" + string.Join(", ", Arguments) + ")";
        }
        /// <summary>
        /// возвращает null если такого аргумента нет
        /// </summary>
        /// <param name="position"></param>
        /// <returns></returns>
        public string Argument(int position)
        {
            return Arguments.ElementAtOrDefault(position);
        }

        /// <summary>
        /// возвращает defaultValue если такого аргумента нет
        /// </summary>
        /// <param name="position"></param>
        /// <param name="defaultValue"></param>
        /// <returns></returns>
        public string Argument(int position, string defaultValue)
        {
            return Argument(position) ?? defaultValue;
        }
    }

    public class MemoryManager
    {
        public BlackMagic BM;
        public KeyBoard KB;
        private Dictionary<double[], uint> DynamicDoublePatternCache = new Dictionary<double[],uint>();
        private static double[] signature = {901791, 349667, 371721, 139443, 213674};
        private AddonMessage LastMessage;
        private int LastProcessedMessage = -1;

        public ObjectManager ObjectManager
        {
            get
            {
                return new ObjectManager(BM, pObjectManager);
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

        #region Properties

        public uint pClientConnection
        {
            get { return BM.ReadUInt(BM.ReadUInt(FindPattern(Patterns.ClientConnection))); }
        }

        public uint pObjectManager
        {
            get { return BM.ReadUInt(pClientConnection + BM.ReadUInt(FindPattern(Patterns.ObjectManagerOffset))); }
        }

        #endregion

        public MemoryManager(int id)
        {
            BM = new BlackMagic(id);
            KB = new KeyBoard(BM.WindowHandle);
            LastMessage = null;
        }

        #region Pattern Methods
        private bool CheckPattern(Pattern pattern, uint cached)
        {

            string[] saPattern = pattern.PatternString.Split(' ');
            byte[] bPattern = new byte[saPattern.Length];

            for (int i = 0; i < bPattern.Length; i++)
                bPattern[i] = Convert.ToByte(saPattern[i], 0x10);

            try
            {
                // вообще говоря если данные верны то паттерн будет находиться по адресу
                // cached - pattern.Offset, но при ошибке WoW.FindPattern() вернёт dwStart
                // так что делать dwStart == cached - pattern.Offset нельзя, уменьшаем на 1
                uint answer = BM.FindPattern(cached - pattern.Offset - 1, pattern.PatternString.Length + 1, bPattern, pattern.Mask);
                return cached == answer + pattern.Offset;
            }
            catch (Exception)
            {
                return false;
            }
        }

        private uint FindPattern(Pattern pattern)
        {
            if (Settings.Default.FindPatternCache.ContainsKey(pattern))
            {
                uint cached = Settings.Default.FindPatternCache[pattern];
                bool ok = true;
                try
                {
                    if (!CheckPattern(pattern, cached))
                        ok = false;
                }
                catch
                {
                    ok = false;
                }
                if (ok)
                    return cached;
                else
                {
                    Log("кэшированный оффсет FindPattern(" + pattern + ") == 0x" + cached.ToString("X8") + " устарел, ищем заново");
                    Settings.Default.FindPatternCache.Remove(pattern);
                    Settings.Default.Save();
                }
            }
            uint ans = BM.FindPattern(pattern.PatternString, pattern.Mask);
            if (ans == (uint)BM.MainModule.BaseAddress) throw new ApplicationException("Pattern not found");

            Settings.Default.FindPatternCache[pattern] = ans + pattern.Offset;
            Log("найден новый оффсет FindPattern(" + pattern + ") == 0x" +
                Settings.Default.FindPatternCache[pattern].ToString("X8"));

            Settings.Default.Save();
            return Settings.Default.FindPatternCache[pattern];
        }

        private uint FindPattern(uint pattern)
        {
            return pattern;
        } 
        #endregion

        #region DllImport

        /// <summary>
        /// The GetForegroundWindow function returns a handle to the foreground window.
        /// </summary>
        [DllImport("user32.dll")]
        static extern IntPtr GetForegroundWindow();

        #endregion

        /// <summary>
        /// возвращает тру если окно WoW сейчас активно
        /// </summary>
        /// <returns></returns>
        public bool IsWoWForeground()
        {
            return BM.WindowHandle == GetForegroundWindow();
        }

        public GameState CurrentGameState
        {
            get
            {
                string state = BM.ReadASCIIString(Patterns.GameState, 100);
                if (state == "login")
                    return GameState.Login;

                else if (state == "realmwizard")
                    return GameState.RealmWizard;

                else if (state == "charselect")
                    if (pObjectManager == 0)
                        return GameState.Character;
                    else
                        return GameState.World;

                else if (state == "")
                    return GameState.None;

                else
                    throw new Exception(state);
            }
        }

        public void WaitForInputIdle()
        {
            // такая штука тоже часто срабатывает раньше времени
            Process.GetProcessById(BM.ProcessId).WaitForInputIdle();
            TimeSpan responseTime;
            do
            {
                DateTime before = DateTime.Now;
                KB.PressKey(Key.LeftCtrl, true);
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

        private uint CachedDoublePattern(double[] pattern)
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
                    return cached;
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
        private uint FindDoublePattern(double[] pattern)
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
                            if (!Settings.Default.AddonSignatureStatistics.ContainsKey(pattern))
                                Settings.Default.AddonSignatureStatistics[pattern] = new List<uint>();
                            Settings.Default.AddonSignatureStatistics[pattern].Add(pos);
                            Settings.Default.Save();
                            return pos;
                        }
                    }
            return 0;
        }

        private uint FindDoublePattern(uint start, uint readBytes, double[] pattern)
        {
            uint readDoubles = readBytes / 8;

            double[] buffer = ReadDoubles(start, readDoubles);

            if (buffer == null) return 0;

            int finish = (int)readDoubles - pattern.Length;


            for (int i = 0; i < finish; ++i)
            {
                bool ok = true;

                for (int j = 0, p = i; ok && j < pattern.Length; ++j, p += 2)
                    if (pattern[j] != buffer[p])
                        ok = false;

                if (ok)
                    return start + (uint)i * 8;
            }
            return 0;
        }

        private bool CheckDoublePattern(uint start, double[] pattern)
        {
            return FindDoublePattern(start, (uint)pattern.Length * 16, pattern)==start;
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

        private string[] GetRawAddonMessage(double[] signature)
        {
            uint p = CachedDoublePattern(signature);
            if (p == 0) return null;
            uint pMessage = BM.ReadUInt(p + 16 * (uint)signature.Length);
            uint pTarget = BM.ReadUInt(p + 16 * ((uint)signature.Length + 1));
            uint pDoNotRestart = BM.ReadUInt(p + 16 * ((uint)signature.Length + 2));
            uint pNeedPurchaseConfirmation = BM.ReadUInt(p + 16 * ((uint)signature.Length + 3));
            // http://www.mmowned.com/forums/wow-memory-editing/108898-memory-reading-chat-w-help-add.html#post717199
            string text = BM.ReadUTF8String(pMessage + 0x14, BM.ReadUInt(pMessage+0x10));
            string target = BM.ReadUTF8String(pTarget + 0x14, BM.ReadUInt(pTarget+0x10));
            string DoNotRestart = BM.ReadUTF8String(pDoNotRestart + 0x14, BM.ReadUInt(pDoNotRestart + 0x10));
            string NeedPurchaseConfirmation =
                BM.ReadUTF8String(pNeedPurchaseConfirmation + 0x14, BM.ReadUInt(pNeedPurchaseConfirmation + 0x10));
            return new string[] { text, target, DoNotRestart, NeedPurchaseConfirmation };
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
            if (raw == null) return lastIfPatternFailed ? LastMessage : null;
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
            result.NeedPurchaseConfirmation = raw[3] != "";
            return LastMessage = result;
        }

        public AddonMessage RescanAddonMessage()
        {
            FindDoublePattern(signature);
            return GetAddonMessage(false);
        }

        public bool NewAddonMessage()
        {
            return GetAddonMessage()!=null && GetAddonMessage().Id > LastProcessedMessage;
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

    }
}
