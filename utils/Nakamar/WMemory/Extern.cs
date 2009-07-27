using System;
using System.Collections;
using System.Runtime.InteropServices;

namespace WoWMemoryManager
{
    #region structs and enums

    [StructLayout(LayoutKind.Sequential)]
    public struct SYSTEM_INFO
    {
        public ushort processorArchitecture;
        ushort reserved;
        public uint pageSize;
        public IntPtr minimumApplicationAddress;
        public IntPtr maximumApplicationAddress;
        public IntPtr activeProcessorMask;
        public uint numberOfProcessors;
        public uint processorType;
        public uint allocationGranularity;
        public ushort processorLevel;
        public ushort processorRevision;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct MEMORY_BASIC_INFORMATION
    {
        public UInt32 BaseAddress;
        public UInt32 AllocationBase;
        public UInt32 AllocationProtect;
        public UInt32 RegionSize;
        public MemoryState State;
        public UInt32 Protect;
        public MemoryType lType;
    }

    /// <summary>
    /// http://msdn.microsoft.com/ru-ru/library/aa366775(en-us,VS.85).aspx
    /// </summary>
    public enum MemoryState : uint
    {
        MEM_COMMIT = 0x1000,
        MEM_FREE = 0x10000,
        MEM_RESERVE = 0x2000,
    }

    public enum MemoryType : uint
    {
        MEM_IMAGE = 0x1000000,
        MEM_MAPPED = 0x40000,
        MEM_PRIVATE = 0x20000,
    }

    /// <summary>
    /// http://msdn.microsoft.com/ru-ru/library/aa366786(en-us,VS.85).aspx
    /// </summary>
    public enum ProtectStatus : uint
    {
        EXECUTE = 0x10,
        EXECUTE_READ = 0x20,
        EXECUTE_READWRITE = 0x40,
        EXECUTE_WRITECOPY = 0x80,
        NOACCESS = 0x01,
        READONLY = 0x02,
        READWRITE = 0x04,
        WRITECOPY = 0x08
    }

    public enum ProtectStatusModifiers : uint
    {
        NOMODIFIERS = 0,
        GUARD = 0x100,
        NOCACHE = 0x200,
        WRITECOMBINE = 0x400,
    }

    #endregion

    /// <summary>
    /// разные DllImport и обертки для них
    /// </summary>
    public static class Extern
    {
        private static SYSTEM_INFO _systemInfo;
        public static SYSTEM_INFO SystemInfo { get {return _systemInfo; } }

        #region DllImport

        /// <summary>
        /// If the function fails, the return value is zero. To get extended error information, call GetLastError.
        /// </summary>
        /// <param name="hWnd"></param>
        /// <param name="Msg"></param>
        /// <param name="wParam"></param>
        /// <param name="lParam"></param>
        /// <returns></returns>
        [return: MarshalAs(UnmanagedType.Bool)]
        [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        public static extern bool PostMessage(IntPtr hWnd, UInt32 Msg, UInt32 wParam,
           UInt32 lParam);

        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        public static extern short VkKeyScan(char ch);

        [DllImport("user32.dll")]
        public static extern IntPtr GetForegroundWindow();

        [DllImport("user32.dll")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool SetForegroundWindow(IntPtr hWnd);

        [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        public static extern IntPtr FindWindowEx(IntPtr hwndParent, IntPtr hwndChildAfter, string lpszClass, string lpszWindow);

        [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        public static extern IntPtr FindWindowEx(IntPtr parentHandle, IntPtr childAfter, string className, IntPtr windowTitle);

        [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        public static extern IntPtr FindWindow(string lpClassName, string lpWindowName);

        [DllImport("user32.dll", EntryPoint = "FindWindow", SetLastError = true, CharSet = CharSet.Auto)]
        public static extern IntPtr FindWindowByCaption(IntPtr ZeroOnly, string lpWindowName);

        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        public static extern uint MapVirtualKey(uint uCode, uint uMapType);

        [DllImport("kernel32.dll")]
        public static extern void GetSystemInfo(out SYSTEM_INFO lpSystemInfo);

        [DllImport("kernel32.dll")]
        static extern uint VirtualQueryEx(IntPtr hProcess, IntPtr lpAddress,
           out MEMORY_BASIC_INFORMATION lpBuffer, uint dwLength);

        #endregion

        static Extern()
        {
            GetSystemInfo(out _systemInfo);
        }

        #region Wrappers

        /// <summary>
        /// перебирает все участки адресного пространства процесса
        /// </summary>
        public static RangesEnumerable EnumerateMemoryRanges(IntPtr hProcess)
        {
            return new RangesEnumerable(hProcess);
        }

        public class RangesEnumerable : IEnumerable
        {
            private IntPtr hProcess;

            public RangesEnumerable(IntPtr hProcess) : base()
            {
                this.hProcess = hProcess;
            }

            #region Члены IEnumerable

            public IEnumerator GetEnumerator()
            {
                uint address = (uint)SystemInfo.minimumApplicationAddress.ToInt32();
                do
                {
                    MEMORY_BASIC_INFORMATION m = new MEMORY_BASIC_INFORMATION();
                    if (VirtualQueryEx(hProcess, new IntPtr(address), out m, (uint)Marshal.SizeOf(m))
                        != Marshal.SizeOf(m))
                        throw new Exception("VirtualQueryEx failed");
                    if (m.BaseAddress != address)
                        throw new Exception("Something wrong");
                    address += m.RegionSize;
                    yield return m;
                }
                while (address < (uint)SystemInfo.maximumApplicationAddress.ToInt32());
                yield break;
            }

            public System.Collections.Generic.Stack<MEMORY_BASIC_INFORMATION> Reverse()
            {
                System.Collections.Generic.Stack<MEMORY_BASIC_INFORMATION> s =
                    new System.Collections.Generic.Stack<MEMORY_BASIC_INFORMATION>();

                foreach (MEMORY_BASIC_INFORMATION m in this)
                    s.Push(m);

                return s;

            }

            #endregion
        }



        #endregion
 
    }
}
