using System;
using System.Collections;
using System.Collections.Generic;
using Util;
using Magic;
using System.Diagnostics;

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

    public class MemoryManager
    {
        private BlackMagic WoW;
        private uint ppClientConnection;
        private uint ObjectManagerOffset;
        public uint pClientConnection
        {
            get
            {
                return WoW.ReadUInt(ppClientConnection);
            }
        }
        public Hashtable Cache;
        

        public MemoryManager(int id, Hashtable cache)
        {
            WoW = new BlackMagic(id);
            Cache = cache;
                     
            ppClientConnection = WoW.ReadUInt(FindPattern(Patterns.ClientConnection));
            ObjectManagerOffset = WoW.ReadUInt(FindPattern(Patterns.ObjectManagerOffset));
        }

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
                uint answer = WoW.FindPattern(cached - pattern.Offset - 1, pattern.PatternString.Length + 1, bPattern, pattern.Mask);
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
            uint ans = WoW.FindPattern(pattern.PatternString, pattern.Mask);
            if (ans == (uint)WoW.MainModule.BaseAddress) throw new ApplicationException("Pattern not found");

            Cache[key] = ans + pattern.Offset;
            Logger.Log("найден новый оффсет FindPattern(" + key + ") == " + ((uint)Cache[key]).ToString("X"));
            return (uint)Cache[key];
        }

        /// <summary>
        /// The GetForegroundWindow function returns a handle to the foreground window.
        /// </summary>
        [System.Runtime.InteropServices.DllImport("user32.dll")]
        static extern IntPtr GetForegroundWindow();

        /// <summary>
        /// возвращает тру если окно WoW сейчас активировано
        /// </summary>
        /// <returns></returns>
        public bool IsWoWForeground()
        {
            return Process.GetProcessById(WoW.ProcessId).MainWindowHandle == GetForegroundWindow();
        }

    }
}
