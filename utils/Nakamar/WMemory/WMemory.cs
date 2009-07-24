using System;
using Magic;

/*
// вычисляем оффсеты
// 007C0799 - 8b 0d 80 9f 13 01          - mov ecx,[01139f80]
// 007C079F - 89 81 34 2c 00 00          - mov [ecx+00002c34],eax

// [[01139f80] + 00002c34]

// FindPattern(Patterns.ClientConnection) - здесь находится вышеуказанный код, ~007C0799
// WoW.ReadUInt(FindPattern(Patterns.ClientConnection)) - адрес указателя на ClientConnection, 01139f80
// WoW.ReadUInt(WoW.ReadUInt(FindPattern(Patterns.ClientConnection))) указатель на ClientConnection 

uint ppClientConnection = WoW.ReadUInt(WoW.ReadUInt(FindPattern(Patterns.ClientConnection)));         

uint ObjectManagerOffset = WoW.ReadUInt(FindPattern(Patterns.ObjectManagerOffset));

uint pObjectManager = WoW.ReadUInt(pClientConnection + ObjectManagerOffset);
*/

namespace WoWMemoryManager
{

    public class MemoryManager
    {
        private BlackMagic WoW;

        public MemoryManager(int id)
        {
            WoW = new BlackMagic(id);

        }

        private uint FindPattern(Pattern pattern)
        {
            uint ans = WoW.FindPattern(pattern.PatternString, pattern.Mask);
            if (ans == (uint)WoW.MainModule.BaseAddress) throw new ApplicationException("Pattern not found");
            return ans + pattern.Offset;
        }
        
        

    }
}
