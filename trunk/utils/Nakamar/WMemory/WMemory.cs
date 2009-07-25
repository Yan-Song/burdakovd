using System;
using System.Collections;
using System.ComponentModel;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using Magic;
using Util;

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
    public enum GameState { Login, Character, World };

    public class MemoryManager
    {
        public BlackMagic BM;
        public Hashtable Cache;

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

        public MemoryManager(int id, Hashtable cache)
        {
            BM = new BlackMagic(id);
            Cache = cache;
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
            string key = pattern.PatternString + ", " + pattern.Mask + ", " + pattern.Offset;
            if (Cache.Contains(key) && Cache[key] is uint)
            {
                uint cached = (uint)Cache[key];
                if (CheckPattern(pattern, cached))
                    return cached;
                else
                {
                    Logger.Log("кэшированный оффсет FindPattern(" + key + ") == " + cached.ToString("X") + " устарел, ищем заново");
                    Cache.Remove(key);
                }
            }
            uint ans = BM.FindPattern(pattern.PatternString, pattern.Mask);
            if (ans == (uint)BM.MainModule.BaseAddress) throw new ApplicationException("Pattern not found");

            Cache[key] = ans + pattern.Offset;
            Logger.Log("найден новый оффсет FindPattern(" + key + ") == " + ((uint)Cache[key]).ToString("X"));
            return (uint)Cache[key];
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

        /// <summary>
        /// If the function fails, the return value is zero. To get extended error information, call GetLastError.
        /// </summary>
        /// <param name="hWnd"></param>
        /// <param name="Msg"></param>
        /// <param name="wParam"></param>
        /// <param name="lParam"></param>
        /// <returns></returns>
        [return: MarshalAs(UnmanagedType.Bool)]
        [DllImport("user32.dll", SetLastError = true)]
        static extern bool PostMessage(HandleRef hWnd, uint Msg, IntPtr wParam,
           IntPtr lParam);

        #endregion

        void PostMessageSafe(HandleRef hWnd, uint msg, IntPtr wParam, IntPtr lParam)
        {
            bool returnValue = PostMessage(hWnd, msg, wParam, lParam);
            if (!returnValue)
                throw new Win32Exception(Marshal.GetLastWin32Error());
        }

        /// <summary>
        /// возвращает тру если окно WoW сейчас активировано
        /// </summary>
        /// <returns></returns>
        public bool IsWoWForeground()
        {
            return Process.GetProcessById(BM.ProcessId).MainWindowHandle == GetForegroundWindow();
        }

        public GameState CurrentGameState()
        {
            string state = BM.ReadASCIIString(Patterns.GameState, 100);
            if (state == "login")
                return GameState.Login;
            else if (state == "charselect")
                if (pObjectManager == 0)
                    return GameState.Character;
                else
                    return GameState.World;
            else
                throw new Exception();
        }

        #region SendKeys

        public void SendKeys(Keys k)
        {
            if (!IsWoWForeground()) return;
            throw new NotImplementedException();
        }

        public void SendKeys(string p)
        {
            if (!IsWoWForeground()) return;
            throw new NotImplementedException();
        }

        #endregion

        public void WaitForInputIdle()
        {
            Process.GetProcessById(BM.ProcessId).WaitForInputIdle();
        }
    }
}
