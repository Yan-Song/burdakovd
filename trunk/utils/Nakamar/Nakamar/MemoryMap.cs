using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Nakamar
{
    /// <summary>
    /// структура хранения паттерна, которым можно будет пользоваться в SearchPattern
    /// </summary>
    public struct Pattern
    {
        public string PatternString;
        public int Offset;
        /// <param name="pattern">Паттерн, в виде последовательности байтов в шестнадцатеричном виде.
        /// Байты разделяются пробелами.
        /// Если значение какого-то байта может быть любым - то вместо него "XX".
        /// Пример: "64 8B 15 XX XX XX XX 8B 34 XX 8B 0D XX XX XX XX 89 81"
        /// </param>
        /// <param name="offset">Смещение, в каком месте паттерна находится интересующая информация, индексация с 0</param>
        public Pattern(string pattern, int offset)
        {
            PatternString = pattern;
            Offset = offset;
        }
    }

    /// <summary>
    /// здесь хранятся данные о смещениях WoW, которые могут измениться со следующим патчем
    /// </summary>
    public class MemoryMap
    {
        /// <summary>
        /// адрес структуры g_clientConnection
        /// </summary>
        public static Pattern ClientConnection = new Pattern("64 8B 15 XX XX XX XX 8B 34 XX 8B 0D XX XX XX XX 89 81", 12);
        
        /// <summary>
        /// смещение адреса ObjectManager относительно ClientConnection
        /// </summary>
        public static Pattern ObjectManagerOffset = 
            new Pattern("64 8B 15 XX XX XX XX 8B 34 XX 8B 0D XX XX XX XX 89 81 XX XX XX XX 8B 15", 18);

    }
}
