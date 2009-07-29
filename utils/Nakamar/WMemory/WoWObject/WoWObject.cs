using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Magic;

// most of code from here: http://www.mmowned.com/forums/wow-memory-editing/208754-guide-kind-how-i-handle-objects.html

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
        protected const uint GuidOffset = 0x30,
            TypeOffset = 0x14,
            DescriptorFieldsOffset = 0x8,
            XPositionOffset = 0x7D0,
            YPositionOffset = 0x7D4,
            ZPositionOffset = 0x7D8,
            RotationOffset = 0x7DC;

        protected BlackMagic Reader;

        public override string ToString()
        {
            return "WoW Object at 0x" + BaseAddress.ToString("X") + " GUID: 0x" + Guid.ToString("X");
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
            get { return (ObjectType)Reader.ReadUInt(BaseAddress + TypeOffset); }
        }

        public virtual ulong Guid
        {
            get { return Reader.ReadUInt64(BaseAddress + GuidOffset); }
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
        public float Rotation
        {
            get { return Reader.ReadFloat(BaseAddress + RotationOffset); }
        }
    }


    public class CreatureObject : WoWObject
    {
        protected const uint //LevelOffset = 0x35 * 4,
            //CurrentHealthOffset = 0x17 * 4,
            //MaxHealthOffset = 0x1F * 4,
            //CurrentManaOffset = 0x18 * 4,
            //MaxManaOffset = 0x20 * 4,
            TargetGuidOffset = 0x12 * 4;

        public CreatureObject(BlackMagic reader, uint baseAddress)
            : base(reader, baseAddress)
        { }

        /*public float Pitch
        {
            get { return Reader.ReadFloat(Reader.ReadUInt(BaseAddress + 0x110) + 0x20); }
        }*/

        public ulong TargetGuid
        {
            get { return Reader.ReadUInt64(DescriptorFields + TargetGuidOffset); }
        }

        /*public int Level
        {
            get { return Reader.ReadInt(DescriptorFields + LevelOffset); }
        }

        public int CurrentHealth
        {
            get { return Reader.ReadInt(DescriptorFields + CurrentHealthOffset); }
        }

        public int MaxHealth
        {
            get { return Reader.ReadInt(DescriptorFields + MaxHealthOffset); }
        }

        public int CurrentMana
        {
            get { return Reader.ReadInt(DescriptorFields + CurrentManaOffset); }
        }

        public int MaxMana
        {
            get { return Reader.ReadInt(DescriptorFields + MaxManaOffset); }
        }

        public int HealthPercent
        {
            get
            {
                double percentage = CurrentHealth / MaxHealth;
                percentage = percentage * 100;
                return (int)Math.Round(percentage);
            }
        }*/
    }


    public class NpcObject : CreatureObject
    {
        /*protected const uint SummonedByOffset = 0xE * 4,
            AttackingGuidOffset = 0x0A38;
        */
        public NpcObject(BlackMagic reader, uint baseAddress)
            : base(reader, baseAddress)
        { }

        public string Name
        {
            get { return Reader.ReadASCIIString(Reader.ReadUInt(Reader.ReadUInt(BaseAddress + 0x9B0) + 0x3C), 1000); }
        }

        /*public ulong AttackingGuid
        {
            get { return Reader.ReadUInt64(BaseAddress + AttackingGuidOffset); }
        }

        public ulong SummonedBy
        {
            get { return Reader.ReadUInt64(DescriptorFields + SummonedByOffset); }
        }*/
    }


    public class PlayerObject : CreatureObject
    {
        protected const uint CurrentRageOffset = 0x19 * 4,
            CurrentEnergyOffset = 0x1B * 4,
            MaxEnergyOffset = 0x23 * 4;

        public PlayerObject(BlackMagic reader, uint baseAddress)
            : base(reader, baseAddress)
        { }

        /*public int CurrentRage
        {
            get
            {
                int RageTemp = Reader.ReadInt(DescriptorFields + CurrentRageOffset);
                return (int)(Math.Floor((double)(RageTemp / 10)));
            }
        }

        public int MaxRage
        {
            get { return 100; }
        }

        public int CurrentEnergy
        {
            get { return Reader.ReadInt(DescriptorFields + CurrentEnergyOffset); }
        }

        public int MaxEnergy
        {
            get { return Reader.ReadInt(DescriptorFields + MaxEnergyOffset); }
        }*/
    }


    public class GameObject : WoWObject
    {
        protected const uint gameObject_XPosition = 0x10 * 4,
            gameObject_YPosition = 0x11 * 4,
            gameObject_ZPosition = 0x12 * 4,
            displayId = 0x8 * 4;

        public GameObject(BlackMagic reader, uint baseAddress)
            : base(reader, baseAddress)
        { }

        public override string ToString()
        {
            return "Name: " + Name + " X: " + XPosition.ToString() + " Y: " + YPosition.ToString() + " Z: " + ZPosition.ToString();
        }

        public string Name
        {
            get
            {
                return Reader.ReadASCIIString(Reader.ReadUInt(BaseAddress + 0x1f4) + 0x078, 1000);
            }
        }

        public override float XPosition
        {
            get { return Reader.ReadFloat(DescriptorFields + gameObject_XPosition); }
        }

        public override float YPosition
        {
            get { return Reader.ReadFloat(DescriptorFields + gameObject_YPosition); }
        }

        public override float ZPosition
        {
            get { return Reader.ReadFloat(DescriptorFields + gameObject_ZPosition); }
        }

        /*public int DisplayId
        {
            get { return Reader.ReadInt(DescriptorFields + displayId); }
        }*/
    }


    /*public class DynamicObject : WoWObject
    {
        protected const uint dynamicObject_XPosition = 0xB * 4,
            dynamicObject_YPosition = 0xC * 4,
            dynamicObject_ZPosition = 0xD * 4;

        public DynamicObject(BlackMagic reader, uint baseAddress)
            : base(reader, baseAddress)
        { }

        public override float XPosition
        {
            get { return Reader.ReadFloat(DescriptorFields + dynamicObject_XPosition); }
        }

        public override float YPosition
        {
            get { return Reader.ReadFloat(DescriptorFields + dynamicObject_YPosition); }
        }

        public override float ZPosition
        {
            get { return Reader.ReadFloat(DescriptorFields + dynamicObject_ZPosition); }
        }
    }*/


    /*public class CorpseObject : WoWObject
    {
        protected const uint corpseObject_XPosition = 0xB * 4,
                corpseObject_YPosition = 0xC * 4,
                corpseObject_ZPosition = 0xD * 4;

        public CorpseObject(BlackMagic reader, uint baseAddress)
            : base(reader, baseAddress)
        { }

        public override float XPosition
        {
            get { return Reader.ReadFloat(DescriptorFields + corpseObject_XPosition); }
        }

        public override float YPosition
        {
            get { return Reader.ReadFloat(DescriptorFields + corpseObject_YPosition); }
        }

        public override float ZPosition
        {
            get { return Reader.ReadFloat(DescriptorFields + corpseObject_ZPosition); }
        }
    }*/
}
