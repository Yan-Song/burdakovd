
using System;

namespace WoWMemoryManager
{
    /// <summary>
    /// структура хранения паттерна, которым можно будет пользоваться в SearchPattern
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
            if (pattern.Length != mask.Length * 3 - 1) throw new System.ArgumentException("несовпадение длин паттерна и маски");
            PatternString = pattern;
            Mask = mask;
            Offset = offset;
        }

        public override string ToString()
        {
            return PatternString + " / " + Mask + ", " + Offset.ToString();
        }
    }

    /// <summary>
    /// здесь хранятся данные о смещениях WoW, которые могут измениться со следующим патчем
    /// </summary>
    static class Patterns
    {
        /// <summary>
        /// адрес структуры g_clientConnection, works for 3.2.0
        /// </summary>
        public static Pattern ClientConnection =
            new Pattern("64 8B 15 00 00 00 00 8B 34 00 8B 0D 00 00 00 00 89 81", "xxx????xx?xx????xx", 12);
        
        /// <summary>
        /// смещение адреса ObjectManager относительно ClientConnection, works for 3.2.0
        /// </summary>
        public static Pattern ObjectManagerOffset = 
            new Pattern("64 8B 15 00 00 00 00 8B 34 00 8B 0D 00 00 00 00 89 81 00 00 00 00 8B 15", "xxx????xx?xx????xx????xx", 18);

        /// <summary>
        /// returns an String with "login" for Login Screen and "charselect" for Charselect Screen.
        /// On entering World its "charselect"
        /// it also can be "" while WoW is starting
        /// and "realmwizard", when you choose a realm
        /// http://www.mmowned.com/forums/wow-memory-editing/241997-3-1-3-some-static-address-found.html
        /// </summary>
        public static uint GameState = 0x010C2138; // works for 3.2.0a

        public static uint PlayerBase = 0x012BEDB8; // for 3.2.0

    }
}
