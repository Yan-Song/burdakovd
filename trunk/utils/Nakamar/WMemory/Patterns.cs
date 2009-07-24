
namespace WoWMemoryManager
{
    /// <summary>
    /// структура хранения паттерна, которым можно будет пользоваться в SearchPattern
    /// </summary>
    struct Pattern
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
    }

    /// <summary>
    /// здесь хранятся данные о смещениях WoW, которые могут измениться со следующим патчем
    /// </summary>
    static class Patterns
    {
        /// <summary>
        /// адрес структуры g_clientConnection
        /// </summary>
        public static Pattern ClientConnection =
            new Pattern("64 8B 15 00 00 00 00 8B 34 00 8B 0D 00 00 00 00 89 81", "xxx????xx?xx????xx", 12);
        
        /// <summary>
        /// смещение адреса ObjectManager относительно ClientConnection
        /// </summary>
        public static Pattern ObjectManagerOffset = 
            new Pattern("64 8B 15 00 00 00 00 8B 34 00 8B 0D 00 00 00 00 89 81 00 00 00 00 8B 15", "xxx????xx?xx????xx????xx", 18);

    }
}
