using Magic;
using WLibrary;
using System;

namespace WoWMemoryManager
{
    /// <summary>
    /// Библиотека WLibrary может работать с любым менеджером памяти, реализующим интерфейс RawMemoryManager
    /// Данный класс позволяет использовать BlackMagic с WLibrary.
    /// </summary>
    public class BlackMagicAdapter : RawMemoryManager
    {
        private BlackMagic BM;

        public BlackMagicAdapter(BlackMagic BM_)
        {
            this.BM = BM_;
        }

        public System.Diagnostics.ProcessModule MainModule
        {
            get { return BM.MainModule; }
        }

        public byte[] ReadBytes(uint dwAddress, int nSize)
        {
            return BM.ReadBytes(dwAddress, nSize);
        }

        public uint ReadUInt(uint dwAddress)
        {
            return BM.ReadUInt(dwAddress);
        }

        public ulong ReadUInt64(uint dwAddress)
        {
            return BM.ReadUInt64(dwAddress);
        }

        public float ReadFloat(uint dwAddress)
        {
            return BM.ReadFloat(dwAddress);
        }

        public uint FindPattern(string szPattern, string szMask)
        {
            return BM.FindPattern(szPattern, szMask);
        }

        public uint FindPattern(uint dwStart, int nSize, byte[] bPattern, string szMask)
        {
            return BM.FindPattern(dwStart, nSize, bPattern, szMask);
        }

        public string ReadASCIIString(uint dwAddress, int nLength)
        {
            return BM.ReadASCIIString(dwAddress, nLength);
        }

        public IntPtr ProcessHandle
        {
            get { return BM.ProcessHandle; }
        }
    }
}
