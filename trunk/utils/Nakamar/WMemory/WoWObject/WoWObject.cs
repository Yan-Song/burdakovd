using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Magic;

// most of code from here: http://www.mmowned.com/forums/wow-memory-editing/208754-guide-kind-how-i-handle-objects.html
// name offsets http://www.mmowned.com/forums/wow-memory-editing/231374-3-1-1-reading-unit-names.html
// some offsets there: http://www.mmowned.com/forums/wow-memory-editing/237345-3-1-3-info-dump.html

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
        protected const uint GuidOffset = 0x30, // works for 3.1.3
            TypeOffset = 0x14, // works for 3.1.3
            DescriptorFieldsOffset = 0x8,
            XPositionOffset = 0x798, // works for 3.1.3
            YPositionOffset = 0x79c, // works for 3.1.3
            ZPositionOffset = 0x7a0, // works for 3.1.3
            RotationOffset = 0x7a8; // works for 3.1.3

        protected const uint // offsets in object descriptor table
            descObjectFieldGuid = 0x0;
            
        protected BlackMagic Reader;

        public override string ToString()
        {
            return "WoW Object with GUID: 0x" + Guid.ToString("X");
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


    public abstract class CreatureObject : WoWObject
    {
        protected const uint //LevelOffset = 0x35 * 4,
            //CurrentHealthOffset = 0x17 * 4,
            //MaxHealthOffset = 0x1F * 4,
            //CurrentManaOffset = 0x18 * 4,
            //MaxManaOffset = 0x20 * 4,
            descTargetGuidOffset = 0x12 * 4;

        public CreatureObject(BlackMagic reader, uint baseAddress)
            : base(reader, baseAddress)
        { }

        public abstract string Name
        {
            get;
        }

        /*public float Pitch
        {
            get { return Reader.ReadFloat(Reader.ReadUInt(BaseAddress + 0x110) + 0x20); }
        }*/

        public ulong TargetGuid
        {
            get { return Reader.ReadUInt64(DescriptorFields + descTargetGuidOffset); }
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

        protected const uint
            NameOffset1 = 0x968,
            NameOffset2 = 0x54;

        public override string Name
        {
            get { return Reader.ReadUTF8String(Reader.ReadUInt(Reader.ReadUInt(BaseAddress + 0x968) + 0x54), 1000); }
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
        /*protected const uint descCurrentRageOffset = 0x19 * 4,
            descCurrentEnergyOffset = 0x1B * 4,
            descMaxEnergyOffset = 0x23 * 4;*/

        public PlayerObject(BlackMagic reader, uint baseAddress)
            : base(reader, baseAddress)
        { }

        /// <summary>
        /// Deep magic copied from BHTool
        /// </summary>
        public override string Name
        {
            get
            {
                uint ptr_NameStore = 0x113ED00 + 8;
                uint off_NameMask = 0x024;
                uint off_NameBase = 0x01c;
                uint off_NameString = 0x020;

                ulong offset;
                uint base_;

                ulong current, mask, shortGUID, testGUID;
                ulong guid = this.Guid;

                mask = Reader.ReadUInt(ptr_NameStore + off_NameMask);
                base_ = Reader.ReadUInt(ptr_NameStore + off_NameBase);

                shortGUID = guid & 0xffffffff;
                if (mask == 0xFFFFFFFF) return "";
                offset = (12 * (mask & shortGUID));

                current = Reader.ReadUInt((uint)(base_ + offset + 8));
                offset = Reader.ReadUInt((uint)(base_ + offset));

                if ((current & 0x1) == 0x1) { return ""; }

                testGUID = Reader.ReadUInt((uint)(current));

                while (testGUID != shortGUID)
                {
                    current = Reader.ReadUInt((uint)(current + offset + 4));

                    if ((current & 0x1) == 0x1) { return ""; }
                    testGUID = Reader.ReadUInt((uint)(current));
                }
                return Reader.ReadUTF8String((uint)current + off_NameString, 1000);
            }
        }

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
        protected const uint descGameObject_XPosition = 0x10 * 4,
            descGameObject_YPosition = 0x11 * 4,
            descGameObject_ZPosition = 0x12 * 4,
            displayId = 0x8 * 4;

        public GameObject(BlackMagic reader, uint baseAddress)
            : base(reader, baseAddress)
        { }

        public string Name
        {
            get
            {
                return Reader.ReadUTF8String(Reader.ReadUInt(BaseAddress + 0x1a4) + 0x88, 1000);
            }
        }

        public override float XPosition
        {
            get { return Reader.ReadFloat(DescriptorFields + descGameObject_XPosition); }
        }

        public override float YPosition
        {
            get { return Reader.ReadFloat(DescriptorFields + descGameObject_YPosition); }
        }

        public override float ZPosition
        {
            get { return Reader.ReadFloat(DescriptorFields + descGameObject_ZPosition); }
        }

        public int DisplayId
        {
            get { return Reader.ReadInt(DescriptorFields + displayId); }
        }
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
