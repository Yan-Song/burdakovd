
using System;
using Util;

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

    /// <summary>
    /// здесь хранятся данные о смещениях WoW, которые могут измениться со следующим патчем
    /// </summary>
    static class Patterns
    {
        /// <summary>
        /// адрес структуры g_clientConnection, works for 4.x
        /// </summary>
        public static Pattern ClientConnection =
            new Pattern("8B 15 FF FF FF FF 89 82 FF FF FF FF 89 81 08 00 00 " +
            "00 8B 0D FF FF FF FF 89 88 D8 00 00 00 " +
            "C7 81 40 19 00 00 FF FF FF FF C7 81 40 39 00 00 FF FF FF FF 8B 88 D8 00 00 00 ",

            "xx????xx????xxxxxxxx????xxxxxxxxxxxx????xxxxxx????xxxxxx", 2);

        /// <summary>
        /// смещение адреса ObjectManager относительно ClientConnection, works for 4.x
        /// </summary>
        public static Pattern ObjectManagerOffset =
            new Pattern("8B 15 FF FF FF FF 89 82 FF FF FF FF 89 81 08 00 00 " +
            "00 8B 0D FF FF FF FF 89 88 D8 00 00 00 " +
            "C7 81 40 19 00 00 FF FF FF FF C7 81 40 39 00 00 FF FF FF FF 8B 88 D8 00 00 00 ",

            "xx????xx????xxxxxxxx????xxxxxxxxxxxx????xxxxxx????xxxxxx", 8);

        /// <summary>
        /// Место в коде, где можно найти адрес gameStateId.
        /// </summary>
        public static Pattern GAME_STATE_1 = new Pattern(StringUtils.join(new String[] {"cc",
            "83 3d FF FF FF FF 00", "75 11", "e8 FF FF FF ??", "8b 10", "8b c8",
            "8b 82 FF 00 00 00", "ff e0", "c3", "cc" }, ' '),
            
            "xxx????xxxx????xxxxxx?xxxxxxx", 3);

        /// <summary>
        /// Место в коде, где можно найти адрес начала массива указателей на строковые представления gameState.
        /// </summary>
        public static Pattern GAME_STATE_2 = new Pattern(StringUtils.join(new String[] {"cc",
            "55", "8b ec", "8b 45 08", "8b 0c 85 FF FF FF FF", "51", "68 FF FF FF FF", "6a 00",
            "e8 FF FF FF FF", "83 c4 FF", "5d", "c3", "cc" }, ' '),
            
            "xxxxxxxxxx????xx????xxx????xx?xxx", 10);

        /// <summary>
        /// Сам составил :), работает для 4.x
        /// </summary>
        public static Pattern PlayerBase =
            new Pattern(StringUtils.join(new String[] {
            "cc", "55", "8b ec", "8b 45 08", "81 ec FF FF FF FF", "53", "8b 5d 10", "57",
            "8b 7d 0c", "8b cf", "0b cb", "a3 FF FF FF FF", "0f 84 FF FF FF FF",
            "8b 15 FF FF FF FF", "0b 15 FF FF FF FF", "56" }, ' '),                
            
            "xxxxxxxxx????xxxxxxxxxxxxx????xx????xx????xx????x", 26);

    }
}
