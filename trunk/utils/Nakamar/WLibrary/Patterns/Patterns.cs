﻿using System;

namespace WLibrary
{
    /// <summary>
    /// здесь хранятся данные о смещениях WoW, которые могут измениться со следующим патчем
    /// </summary>
    public static class Patterns
    {
        /// <summary>
        /// Место в коде, где можно прочитать адрес указателя на структуру ClientConnection.
        /// В случае проблем этот фрагмент кода искать по: ".\ObjectMgrClient.cpp".
        /// Also: ищем на форумах "CurMgrPointer", добавляем к нему WoW PE Header Start Address,
        /// затем ищем получившийся адрес в памяти запущенного процесса WoW (не забываем про Little Endian).
        /// </summary>
        public static Pattern ClientConnection =
            new Pattern(
                "8B 34 8A " + 
                "8B 0D FF FF FF FF " +
                "89 81 FF FF 00 00 " +
                "8B 15 FF FF FF FF " +
                "8B 0D FF FF FF FF " +
                "89 90 FF 00 00 00 " +
                "8B 15 FF FF FF FF " +
                "51",

                "xxx" +
                "xx????" +
                "xx??xx" +
                "xx????" +
                "xx????" +
                "xx?xxx" +
                "xx????" +
                "x",

                5);

        /// <summary>
        /// Место в коде, где можно прочитать смещение указателя на ObjectManager относительно начала структуры ClientConnection.
        /// Как искать - смотри ClientConnection, они в коде рядом.
        /// </summary>
        public static Pattern ObjectManagerOffset =
            new Pattern(
                "8B 34 8A " +
                "8B 0D FF FF FF FF " +
                "89 81 FF FF 00 00 " +
                "8B 15 FF FF FF FF " +
                "8B 0D FF FF FF FF " +
                "89 90 FF 00 00 00 " +
                "8B 15 FF FF FF FF " +
                "51",

                "xxx" +
                "xx????" +
                "xx??xx" +
                "xx????" +
                "xx????" +
                "xx?xxx" +
                "xx????" +
                "x",

                11);

        /// <summary>
        /// Место в коде, где можно прочитать адрес gameStateId.
        /// Cheat-o-matic ftw.
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
    }
}