using System;

namespace WLibrary
{
    /// <summary>
    /// здесь хранятся данные о смещениях WoW, которые могут измениться со следующим патчем
    /// </summary>
    public static class Patterns
    {
        /// <summary>
        /// место в коде, где можно прочитать адрес указателя на структуру ClientConnection
        /// </summary>
        public static Pattern ClientConnection =
            new Pattern(
                "8B 15 FF FF FF FF " + 
                "89 82 FF FF 00 00 " +
                "8B 15 FF FF FF FF " +
                "89 90 FF 00 00 00 " +
                "89 81 FF 00 00 00",

                "xx????" +
                "xx??xx" +
                "xx????" +
                "xx?xxx" +
                "xx?xxx",

                2);

        /// <summary>
        /// место в коде, где можно прочитать смещение указателя на ObjectManager относительно начала структуры ClientConnection
        /// </summary>
        public static Pattern ObjectManagerOffset =
            new Pattern(
                "8B 15 FF FF FF FF " +
                "89 82 FF FF 00 00 " +
                "8B 15 FF FF FF FF " +
                "89 90 FF 00 00 00 " +
                "89 81 FF 00 00 00",

                "xx????" +
                "xx??xx" +
                "xx????" +
                "xx?xxx" +
                "xx?xxx",

                8);

        /// <summary>
        /// место в коде, где можно прочитать адрес gameStateId
        /// </summary>
        public static Pattern GameStateId =
            new Pattern(
                "cc " +
                "83 3d FF FF FF FF 00 " +
                "75 11 " +
                "e8 FF FF FF FF " +
                "8b 10 " +
                "8b c8 " +
                "8b 82 FF 00 00 00 " +
                "ff e0 " +
                "c3 " +
                "cc",
            
                "x" +
                "xx????x" +
                "xx" +
                "x????" +
                "xx" +
                "xx" +
                "xx?xxx" +
                "xx" +
                "x" +
                "x",
                
                3);

        /// <summary>
        /// место в коде, где можно прочитать адрес начала массива указателей на строковые представления gameState
        /// </summary>
        public static Pattern GameStateStringRepresentationBase =
            new Pattern(
                "cc " +
                "55 " +
                "8b ec " +
                "8b 45 08 " +
                "8b 0c 85 FF FF FF FF " +
                "51 " +
                "68 FF FF FF FF " +
                "6a 00 " +
                "e8 FF FF FF FF " +
                "83 c4 FF " +
                "5d " +
                "c3 " +
                "cc",
            
                "x" +
                "x" +
                "xx" +
                "xxx" +
                "xxx????" +
                "x" +
                "x????" +
                "xx" +
                "x????" +
                "xx?" +
                "x" +
                "x" +
                "x",
                
                10);

        /// <summary>
        /// место в коде, где можно прочитать адрес PlayerBase
        /// </summary>
        public static Pattern PlayerBase =
            new Pattern(
                "cc " +
                "55 " +
                "8b ec " +
                "8b 45 08 " +
                "81 ec FF 00 00 00 " +
                "53 " +
                "8b 5d 10 " +
                "57 " +
                "8b 7d 0c " +
                "8b cf " +
                "0b cb " +
                "a3 FF FF FF FF " +
                "0f 84 FF FF 00 00 " +
                "8b 15 FF FF FF FF " +
                "0b 15 FF FF FF FF " +
                "56",
            
                "x" +
                "x" +
                "xx" +
                "xxx" +
                "xx?xxx" +
                "x" +
                "xxx" +
                "x" +
                "xxx" +
                "xx" +
                "xx" +
                "x????" +
                "xx??xx" +
                "xx????" +
                "xx????" +
                "x",
                
                26);

        /// <summary>
        /// место в коде, где можно прочитать адрес начала массива имён игроков, возвращённых из последнего запроса /who
        /// В случае проблем это место кода можно найти по строке "Usage: GetWhoInfo(index)"
        /// </summary>
        public static Pattern LastWhoResultNamesBase =
            new Pattern(
                "d9 7d fe " +
                "0f b7 45 fe " +
                "0d FF FF 00 00 " +
                "89 45 f8 " +
                "83 c4 08 " +
                "d9 6d f8 " +
                "df 7d f4 " +
                "8b 75 f4 " +
                "4e " +
                "d9 6d fe " +
                "3b 35 FF FF FF FF " +
                "0f 83 FF FF 00 00 " +
                "69 f6 FF FF 00 00 " +
                "8d 86 FF FF FF FF " +
                "50 " +
                "57 " +
                "e8 FF FF FF FF",

                "xxx" +
                "xxxx" +
                "x??xx" +
                "xxx" +
                "xxx" +
                "xxx" +
                "xxx" +
                "xxx" +
                "x" +
                "xxx" +
                "xx????" +
                "xx??xx" +
                "xx??xx" +
                "xx????" +
                "x" +
                "x" +
                "x????",

                51);

        /// <summary>
        /// место в коде, где можно прочитать количество байт, выделяемых для каждого имени игрока в массиве /who
        /// </summary>
        public static Pattern WhoResultNameLength =
            new Pattern(
                "d9 7d fe " +
                "0f b7 45 fe " +
                "0d FF FF 00 00 " +
                "89 45 f8 " +
                "83 c4 08 " +
                "d9 6d f8 " +
                "df 7d f4 " +
                "8b 75 f4 " +
                "4e " +
                "d9 6d fe " +
                "3b 35 FF FF FF FF " +
                "0f 83 FF FF 00 00 " +
                "69 f6 FF FF 00 00 " +
                "8d 86 FF FF FF FF " +
                "50 " +
                "57 " +
                "e8 FF FF FF FF",

                "xxx" +
                "xxxx" +
                "x??xx" +
                "xxx" +
                "xxx" +
                "xxx" +
                "xxx" +
                "xxx" +
                "x" +
                "xxx" +
                "xx????" +
                "xx??xx" +
                "xx??xx" +
                "xx????" +
                "x" +
                "x" +
                "x????",

                45);
    }
}
