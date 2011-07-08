using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WLibrary
{
    public class CachingPatternFinder : PatternFinder 
    {
        public delegate void LogFunction(string message);

        private RawMemoryManager manager;
        private Dictionary<Pattern, uint> FindPatternCache;
        private LogFunction Log;

        public CachingPatternFinder(RawMemoryManager manager_, LogFunction logger_, Dictionary<Pattern, uint> cache)
        {
            this.manager = manager_;
            this.FindPatternCache = cache;
            this.Log = logger_;
        }

        public CachingPatternFinder(RawMemoryManager manager_, LogFunction logger_)
            : this(manager_, logger_, new Dictionary<Pattern, uint>())
        {
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
                uint answer = manager.FindPattern(cached - pattern.Offset - 1, pattern.PatternString.Length + 1, bPattern, pattern.Mask);
                return cached == answer + pattern.Offset;
            }
            catch (Exception)
            {
                return false;
            }
        }

        public uint FindPattern(Pattern pattern)
        {
            if (FindPatternCache.ContainsKey(pattern))
            {
                uint cached = FindPatternCache[pattern];
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
                    FindPatternCache.Remove(pattern);
                }
            }

            uint ans = manager.FindPattern(pattern.PatternString, pattern.Mask);
            if (ans == (uint)manager.MainModule.BaseAddress)
                throw new ApplicationException("Pattern not found");

            FindPatternCache[pattern] = ans + pattern.Offset;
            Log("найден новый оффсет FindPattern(" + pattern + ") == 0x" + FindPatternCache[pattern].ToString("X8"));

            return FindPatternCache[pattern];
        }

    }
}
