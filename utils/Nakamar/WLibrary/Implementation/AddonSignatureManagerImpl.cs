using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Runtime.InteropServices;
using Util;

namespace WLibrary
{
    public class AddonSignatureManagerImpl : AddonSignatureManager
    {
        /// <summary>
        /// cache
        /// </summary>
        private Dictionary<EquatableList<double>, uint> cache = new Dictionary<EquatableList<double>, uint>();
        private RawMemoryManager manager;
        private Logger.LogFunction logger;

        public AddonSignatureManagerImpl(RawMemoryManager manager, Logger.LogFunction logger)
        {
            this.manager = manager;
            this.logger = logger;
        }

        private uint FindDoublePattern(uint start, uint readBytes, EquatableList<double> pattern)
        {
            uint readDoubles = readBytes / 8;

            double[] buffer = ReadDoubles(start, readDoubles);

            if (buffer == null) return 0;

            int finish = (int)readDoubles - pattern.Count;

            for (int i = 0; i < finish; ++i)
            {
                bool ok = true;

                for (int j = 0, p = i; ok && j < pattern.Count; ++j, p += 2)
                    if (pattern[j] != buffer[p])
                        ok = false;

                if (ok)
                    return start + (uint)i * 8;
            }
            return 0;
        }

        private bool CheckDoublePattern(uint start, EquatableList<double> pattern)
        {
            return FindDoublePattern(start, (uint)pattern.Count * 16, pattern) == start;
        }

        private double[] ReadDoubles(uint start, uint readDoubles)
        {
            Debug.Assert(sizeof(byte) * 8 == sizeof(double));

            byte[] data = manager.ReadBytes(start, (int)readDoubles * 8);
            Debug.Assert(data.Length == readDoubles * 8);
            double[] result = new double[readDoubles];
            
            IntPtr tmp = Marshal.AllocHGlobal(data.Length);
            Marshal.Copy(data, 0, tmp, data.Length);
            Marshal.Copy(tmp, result, 0, result.Length);
            Marshal.FreeHGlobal(tmp);

            return result;
        }

        public uint Cached(EquatableList<double> signature)
        {
            if (cache.ContainsKey(signature))
            {
                uint cached = cache[signature];

                try
                {
                    if (CheckDoublePattern(cached, signature))
                    {
                        return cached;
                    }
                }
                catch
                {
                }

                cache.Remove(signature);
                logger("Сигнатура аддона потеряна");
            }
            return 0;
        }

        public uint Search(EquatableList<double> signature)
        {
            uint cached = Cached(signature);

            if (cached != 0)
            {
                return cached;
            }

            DateTime startTime = DateTime.Now;

            uint bufferSize = 1 << 26;
            try
            {
                foreach (MEMORY_BASIC_INFORMATION m in Extern.EnumerateMemoryRanges(manager.ProcessHandle))
                {
                    if (m.State == MemoryState.MEM_COMMIT &&
                        m.lType == MemoryType.MEM_PRIVATE &&
                        m.Protect == (uint)ProtectStatus.READWRITE)

                        for (uint start = m.BaseAddress; start < m.BaseAddress + m.RegionSize; start += bufferSize)
                        {
                            uint readBytes = Math.Min(bufferSize, m.BaseAddress + m.RegionSize - start);
                            uint pos = FindDoublePattern(start, readBytes, signature);
                            if (pos != 0)
                            {
                                logger("Сигнатура аддона найдена по адресу 0x" +
                                    pos.ToString("X8") + " за " + (DateTime.Now - startTime) + " сек.");
                                cache[signature] = pos;
                                return pos;
                            }
                        }
                }
                logger("Попытка найти сигнатуру аддона оказалась неуспешной. Поиск занял " + (DateTime.Now - startTime) + " сек.");
            }
            catch (Exception exception)
            {
                logger("Ошибка при поиске сигнатуры аддона: " + exception.Message);
                return 0;
            }
            return 0;
        }

        public void ClearCache()
        {
            cache.Clear();
        }
    }
}
