using System;

namespace WLibrary
{
    public interface RawMemoryManager : RawMemoryReader, RawPatternFinder
    {
        IntPtr ProcessHandle { get; }
    }
}
