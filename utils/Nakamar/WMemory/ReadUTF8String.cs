using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Magic;

namespace WoWMemoryManager
{
    public static class BlackMagicExtension
    {
        public static string ReadUTF8String(this BlackMagic BM, uint address, uint maxLength)
        {
            byte[] bytes = BM.ReadBytes(address, (int)maxLength).TakeWhile(c => c != 0).ToArray(); // удаляем лишнее после \0
            return System.Text.Encoding.UTF8.GetString(bytes);
        }
    }
}
