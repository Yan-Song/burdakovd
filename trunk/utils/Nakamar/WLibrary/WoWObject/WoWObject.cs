using System;

namespace WLibrary
{
    public class WoWObject
    {
        // 5.0.4
        private const uint
            XPositionOffset = 0x7e0,
            YPositionOffset = 0x7e4,
            ZPositionOffset = 0x7e8,
            RotationOffset = 0x7f0;

        private Func<uint> BaseAddress;
        private RawMemoryReader Reader;

        public WoWObject(RawMemoryReader reader, Func<uint> baseAddress)
        {
            this.BaseAddress = baseAddress;
            this.Reader = reader;
        }

        public float XPosition
        {
            get { return Reader.ReadFloat(BaseAddress() + XPositionOffset); }
        }

        public float YPosition
        {
            get { return Reader.ReadFloat(BaseAddress() + YPositionOffset); }
        }

        public float ZPosition
        {
            get { return Reader.ReadFloat(BaseAddress() + ZPositionOffset); }
        }

        public Point Location
        {
            get { return new Point(XPosition, YPosition, ZPosition); }
        }

        public float Rotation
        {
            get { return Reader.ReadFloat(BaseAddress() + RotationOffset); }
        }

        public override string ToString()
        {
            return string.Format("WoW Object with X = {0}, Y = {1}, Z = {2}",
                                 XPosition,
                                 YPosition,
                                 ZPosition);
        }
    }

    public class LocalPlayer : WoWObject
    {
        // 5.0.4
        private const uint
            PlayerBaseOffset1 = 0x48,
            PlayerBaseOffset2 = 0x24; 

        private static uint getPlayerBase(RawMemoryReader reader, PatternFinder patternFinder)
        {
            uint p = reader.ReadUInt(reader.ReadUInt(patternFinder.FindPattern(Patterns.PlayerBase)));
            p = reader.ReadUInt(p + PlayerBaseOffset1);
            p = reader.ReadUInt(p + PlayerBaseOffset2);
            return p;
        }

        private static uint getPlayerBase(RawMemoryReader reader, uint baseAddressPtr)
        {
            uint p0 = reader.ReadUInt(baseAddressPtr);
            uint p1 = reader.ReadUInt(p0 + PlayerBaseOffset1);
            uint p2 = reader.ReadUInt(p1 + PlayerBaseOffset2);
            return p2;
        }

        public LocalPlayer(RawMemoryReader reader, PatternFinder patternFinder)
            : base(reader, () => getPlayerBase(reader, patternFinder))
        {
        }

        public LocalPlayer(RawMemoryReader reader, uint baseAddressPtr)
            : base(reader, () => getPlayerBase(reader, baseAddressPtr))
        {
        }
    }
}
