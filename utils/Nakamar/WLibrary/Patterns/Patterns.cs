using System;

namespace WLibrary
{
    /// <summary>
    /// здесь хранятся данные о смещениях WoW, которые могут измениться со следующим патчем
    /// </summary>
    public static class Patterns
    {
        /// <summary>
        /// Место в коде, где можно прочитать адрес указателя на структуру ClientConnection.
        /// 
        /// Ищем на форумах "CurMgrPointer", добавляем к нему WoW PE Header Start Address,
        /// затем ищем получившийся адрес в памяти запущенного процесса WoW (не забываем про Little Endian).
        /// Ещё там неподалеку в коде встречается указатель на строку "ObjectMgrClient.cpp"
        /// 
        /// 5.0.5
        /// </summary>
        public static Pattern ClientConnection =
            new Pattern(
                "8B 0D FF FF FF FF " +
                "D9 EE " +
                "89 81 FF FF 00 00 " +
                "8B 15 FF FF FF FF " +
                "8B 0D FF FF FF FF " +
                "89 90 FF 00 00 00 " +
                "8B 15 FF FF FF FF " +
                "51",

                "xx????" +
                "xx" +
                "xx??xx" +
                "xx????" +
                "xx????" +
                "xx?xxx" +
                "xx????" +
                "x",

                2);

        /// <summary>
        /// Место в коде, где можно прочитать смещение указателя на ObjectManager относительно начала структуры ClientConnection.
        /// Как искать - смотри ClientConnection, они в коде рядом.
        /// 
        /// 5.0.5
        /// </summary>
        public static Pattern ObjectManagerOffset =
            new Pattern(
                "8B 0D FF FF FF FF " +
                "D9 EE " +
                "89 81 FF FF 00 00 " +
                "8B 15 FF FF FF FF " +
                "8B 0D FF FF FF FF " +
                "89 90 FF 00 00 00 " +
                "8B 15 FF FF FF FF " +
                "51",

                "xx????" +
                "xx" +
                "xx??xx" +
                "xx????" +
                "xx????" +
                "xx?xxx" +
                "xx????" +
                "x",

                10);

        /// <summary>
        /// Место в коде, где можно прочитать адрес gameStateId.
        /// Cheat-o-matic ftw.
        /// 
        /// 5.0.5
        /// </summary>
        public static Pattern GameStateId =
            new Pattern(
                "cc " +
                "83 3D FF FF FF FF 00 " +
                "75 11 " +
                "E8 FF FF FF FF " +
                "8B 10 " +
                "8B C8 " +
                "8B 82 FF 00 00 00 " +
                "FF E0 " +
                "C3 " +
                "CC",
            
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
        /// Место в коде, где можно прочитать адрес начала массива указателей на строковые представления gameState.
        /// 
        /// 5.0.5
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
        /// Место в коде, где можно прочитать адрес PlayerBase.
        /// 
        /// 5.0.5
        /// </summary>
        public static Pattern PlayerBase =
            new Pattern(
                "8b 1d FF FF FF FF " +
                "f6 c3 01 " +
                "75 04 " +
                "3b df " +
                "75 02 " +
                "33 db " +
                "f6 c3 01 " +
                "75 FF " +
                "3b df " +
                "74 FF " +
                "f6 43 FF 01",
            
                "xx????" +
                "xxx" +
                "xx" +
                "xx" +
                "xx" +
                "xx" +
                "xxx" +
                "x?" +
                "xx" +
                "x?" +
                "xx?x",
                
                2);
    }
}
