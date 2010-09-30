
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
            if (pattern.Length != mask.Length * 3 - 1) throw new System.ArgumentException("Несовпадение длин паттерна и маски");
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
        /// адрес структуры g_clientConnection, works for 3.3.0
        /// </summary>
        public static Pattern ClientConnection =
            new Pattern("64 8B 15 00 00 00 00 8B 34 00 8B 0D 00 00 00 00 89 81", "xxx????xx?xx????xx", 12);

        /// <summary>
        /// смещение адреса ObjectManager относительно ClientConnection, works for 3.3.0
        /// </summary>
        public static Pattern ObjectManagerOffset =
            new Pattern("64 8B 15 00 00 00 00 8B 34 00 8B 0D 00 00 00 00 89 81 00 00 00 00 8B 15", "xxx????xx?xx????xx????xx", 18);

        /// <summary>
        /// returns an String with "login" for Login Screen and "charselect" for Charselect Screen.
        /// On entering World its "charselect"
        /// it also can be "" while WoW is starting
        /// and "realmwizard", when you choose a realm
        /// </summary>
        public static Pattern GameState = new Pattern("CC 68 FF FF FF 7F 68 00 00 00 00 68 00 00 00 00 " +
             "E8 00 00 00 00 85 C0 75 11 E8 00 00 00 00 8B 10 8B C8 8B 82 84 00 00 00 FF E0 C3 CC",
             "xxxxxxx????x????x????xxxxx????xxxxxxxxxxxxxx", 12);

        /// <summary>
        /// Сам составил :), работает для 3.2.2 - 3.3.3
        /// </summary>
        public static Pattern PlayerBase =
            new Pattern("55 8B EC 8B 45 08 81 EC 00 01 00 00 56 8B 75 0C 57 8B 7D 10 8B CE 0B CF A3 FF" + 
                " FF FF FF 0F 84 FF FF FF FF D9 E8",
                "xxxxxxxxxxxxxxxxxxxxxxxxx????xx????xx", 25);
        
    }
}
