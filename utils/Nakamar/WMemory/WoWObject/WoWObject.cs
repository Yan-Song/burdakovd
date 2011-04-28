using System;
using Magic;

namespace WoWMemoryManager.WoWObject
{
    public enum ObjectType : uint
    {
        Item = 1, 
        Container = 2,
        NPC = 3,
        Player = 4,
        GameObject = 5,
        DynamicObject = 6,
        Corpse = 7
    }

    public class WoWObject
    {
        protected const uint
            DescriptorFieldsOffset = 0x8,
            XPositionOffset = 0x898,
            YPositionOffset = 0x89c,
            ZPositionOffset = 0x8a0,
            RotationOffset = 0x8a8,
            typeOffset = 0x14;

        protected const uint // offsets in object descriptor table
            descObjectFieldGuid = 0x0;
            
            
        protected BlackMagic Reader;

        public override string ToString()
        {
            return "WoW Object with type: " + Type.ToString() + ", GUID: 0x" + Guid.ToString("X16") +
                " XYZ(" +
                XPosition + ", " + YPosition + ", " + ZPosition +
                ")";
        }

        public WoWObject(BlackMagic reader, uint baseAddress)
        {
            this.BaseAddress = baseAddress;
            this.Reader = reader;
        }

        public uint BaseAddress
        {
            get;
            set;
        }

        protected uint DescriptorFields
        {
            get { return Reader.ReadUInt(BaseAddress + DescriptorFieldsOffset); }
        }

        public ObjectType Type
        {
            get { return (ObjectType)Reader.ReadUInt(BaseAddress+typeOffset); }
        }

        public virtual ulong Guid
        {
            get { return Reader.ReadUInt64(DescriptorFields + descObjectFieldGuid); }
        }

        public virtual float XPosition
        {
            get { return Reader.ReadFloat(BaseAddress + XPositionOffset); }
        }

        public virtual float YPosition
        {
            get { return Reader.ReadFloat(BaseAddress + YPositionOffset); }
        }

        public virtual float ZPosition
        {
            get { return Reader.ReadFloat(BaseAddress + ZPositionOffset); }
        }

        public Util.Point Location
        {
            get { return new Util.Point(XPosition, YPosition, ZPosition); }
        }

        public float Rotation
        {
            get { return Reader.ReadFloat(BaseAddress + RotationOffset); }
        }
    }


    public abstract class CreatureObject : WoWObject
    {
        public CreatureObject(BlackMagic reader, uint baseAddress)
            : base(reader, baseAddress)
        { }
    }


    public class NpcObject : CreatureObject
    {
        public NpcObject(BlackMagic reader, uint baseAddress)
            : base(reader, baseAddress)
        { }

        protected const uint
            NameOffset1 = 0xa0c,
            NameOffset2 = 0x60;

        public virtual string Name
        {
            get
            {
                try
                {
                    return Reader.ReadUTF8String(Reader.ReadUInt(Reader.ReadUInt(BaseAddress + NameOffset1) + NameOffset2), 1000);
                }
                catch
                {
                    return null;
                }
            }
        }
    }


    public class PlayerObject : CreatureObject
    {
        public PlayerObject(BlackMagic reader, uint baseAddress)
            : base(reader, baseAddress)
        { }

    }


    public class GameObject : WoWObject
    {
        protected const uint
            NameOffset1 = 0x1cc,
            NameOffset2 = 0xb4;

        new protected const uint
            XPositionOffset = 0x110;
        new protected const uint
            YPositionOffset = 0x114;
        new protected const uint
            ZPositionOffset = 0x118;

        public GameObject(BlackMagic reader, uint baseAddress)
            : base(reader, baseAddress)
        { }

        public string Name
        {
            get
            {
                try
                {
                    return Reader.ReadUTF8String(Reader.ReadUInt(Reader.ReadUInt(BaseAddress + NameOffset1) + NameOffset2), 1000);
                }
                catch
                {
                    return null;
                }
            }
        }

        public override float XPosition
        {
            get { return Reader.ReadFloat(BaseAddress + XPositionOffset); }
        }

        public override float YPosition
        {
            get { return Reader.ReadFloat(BaseAddress + YPositionOffset); }
        }

        public override float ZPosition
        {
            get { return Reader.ReadFloat(BaseAddress + ZPositionOffset); }
        }

    }
}
