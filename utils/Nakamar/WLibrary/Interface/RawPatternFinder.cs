using System;

namespace WLibrary
{
    /// <summary>
    /// BlackMagic-like interface
    /// </summary>
    public interface RawPatternFinder
    {
        uint FindPattern(string szPattern, string szMask);

        uint FindPattern(uint dwStart, int nSize, byte[] bPattern, string szMask);
    }
}
