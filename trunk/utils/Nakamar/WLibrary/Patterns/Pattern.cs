using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WLibrary
{
    /// <summary>
    /// структура хранения паттерна, которым можно будет пользоваться в PatternFinder
    /// </summary>
    [Serializable]
    public struct Pattern
    {
        public string PatternString;
        public string Mask;
        public uint Offset;
        /// <param name="pattern">Паттерн, в виде последовательности байтов в шестнадцатеричном виде.
        /// Байты разделяются пробелами.
        /// Пример: "64 8B 15 00 00 00 00 8B 34 00 8B 0D 00 00 00 00 89 81"
        /// </param>
        /// <param name="offset">Смещение, в каком месте паттерна находится интересующая информация, индексация с 0</param>
        /// <param name="mask"></param>
        public Pattern(string pattern, string mask, uint offset)
        {
            if (pattern.Length != mask.Length * 3 - 1)
                throw new System.ArgumentException("Несовпадение длин паттерна и маски");

            PatternString = pattern;
            Mask = mask;
            Offset = offset;
        }

        public override string ToString()
        {
            return PatternString + " / " + Mask + ", " + Offset.ToString();
        }
    }
}
