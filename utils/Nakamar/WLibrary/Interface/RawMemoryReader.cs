using System;
using System.Diagnostics;

namespace WLibrary
{
    /// <summary>
    /// BlackMagic-like interface
    /// </summary>
    public interface RawMemoryReader
    {
        /// <summary>
        /// Gets the main module of the opened process.
        /// </summary>
        ProcessModule MainModule { get; }

        /// <summary>
        /// Reads a value from memory
        /// </summary>
        /// <param name="dwAddress">Address at which value will be read.</param>
        /// <param name="nSize">Number of bytes to read from memory.</param>
        /// <returns>Returns the value that was read from memory.</returns>
        byte[] ReadBytes(uint dwAddress, int nSize);

        /// <summary>
        /// Reads a value from memory.
        /// </summary>
        /// <param name="dwAddress">Address at which value will be read.</param>
        /// <returns>Returns the value that was read from memory.</returns>
        uint ReadUInt(uint dwAddress);

        /// <summary>
        /// Reads a value from memory.
        /// </summary>
        /// <param name="dwAddress">Address at which value will be read.</param>
        /// <returns>Returns the value that was read from memory.</returns>
        UInt64 ReadUInt64(uint dwAddress);

        /// <summary>
		/// Reads a value from memory.
		/// </summary>
		/// <param name="dwAddress">Address at which value will be read.</param>
		/// <returns>Returns the value that was read from memory.</returns>
        float ReadFloat(uint dwAddress);

        /// <summary>
		/// Reads a value from memory.
		/// </summary>
		/// <param name="dwAddress">Address at which value will be read.</param>
		/// <param name="nLength">Maximum number of characters to be read.</param>
		/// <returns>Returns the value that was read from memory.</returns>
        string ReadASCIIString(uint dwAddress, int nLength);
    }
}
