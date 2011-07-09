using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WLibrary
{
    public static class RawMemoryReaderExtensionReadUTF8String
    {
        public static string ReadUTF8String(this RawMemoryReader reader, uint address, uint maxLength)
        {
            byte[] bytes = reader.ReadBytes(address, (int)maxLength).TakeWhile(c => c != 0).ToArray(); // удаляем лишнее после \0
            return System.Text.Encoding.UTF8.GetString(bytes);
        }
    }
}
