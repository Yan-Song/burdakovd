using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Magic;
using System.Collections;

namespace WoWMemoryManager.WoWObject
{

    class ObjectList<T> : IEnumerable<T> where T: WoWObject
    {
        private const uint
            firstObjectOffset = 0xB4,          // offset from the object manager to the first object
            nextObjectOffset = 0x3C;           // offset from one object to the next 
        private uint BaseAddress;
        private BlackMagic Reader;

        public ObjectList(BlackMagic reader, uint objectManagerBaseAddress)
        {
            BaseAddress = objectManagerBaseAddress;
            Reader = reader;
        }

        #region Члены IEnumerable

        public IEnumerator GetEnumerator()
        {
            uint CurrentObjectAddress = Reader.ReadUInt(BaseAddress + firstObjectOffset);
            

            while (CurrentObjectAddress != 0 && CurrentObjectAddress % 2 == 0)
            {
                WoWObject CurrentObject = new WoWObject(Reader, CurrentObjectAddress);

                ObjectType type = CurrentObject.Type;
                if (type == ObjectType.NPC)
                    CurrentObject = new NpcObject(Reader, CurrentObjectAddress);
                else if (type == ObjectType.Player)
                    CurrentObject = new PlayerObject(Reader, CurrentObjectAddress);
                else if (type == ObjectType.GameObject)
                    CurrentObject = new GameObject(Reader, CurrentObjectAddress);
                yield return CurrentObject;

                CurrentObjectAddress = Reader.ReadUInt(CurrentObjectAddress + nextObjectOffset);
            }

            yield break;
        }

        #endregion


        #region Члены IEnumerable<T>

        IEnumerator<T> IEnumerable<T>.GetEnumerator()
        {
            {
                foreach (WoWObject w in this)
                    if (w is T)
                        yield return (T)w;
                yield break;
            }
        }

        #endregion
    }


    public class ObjectManager
    {
        private const uint
            PlayerBaseOffset1 = 0x38,
            PlayerBaseOffset2 = 0x24;

        private MemoryManager Memory;
        public uint BaseAddress;               // the address of the object manager
        public IEnumerable<GameObject> GameObjects { get; private set; }
        public IEnumerable<WoWObject> Objects { get; private set; }
        public IEnumerable<NpcObject> NpcObjects { get; private set; }

        public PlayerObject LocalPlayer
        {
            get
            {
                uint p = Memory.pPlayerBase;
                p = Memory.BM.ReadUInt(p + PlayerBaseOffset1);
                p = Memory.BM.ReadUInt(p + PlayerBaseOffset2);
                return new PlayerObject(Memory.BM, p);
            }
        }

        public WoWObject ByGuid(ulong guid)
        {
            foreach(WoWObject w in new ObjectList<WoWObject>(Memory.BM, BaseAddress))
                if(w.Guid == guid)
                    return w;

            throw new KeyNotFoundException("guid " + guid + " not found");
        }

        public ObjectManager(MemoryManager memory, uint objectManagerBaseAddress)
        {
            Memory = memory;
            BaseAddress = objectManagerBaseAddress;
            GameObjects = new ObjectList<GameObject>(Memory.BM, BaseAddress);
            NpcObjects = new ObjectList<NpcObject>(Memory.BM, BaseAddress);
            Objects = new ObjectList<WoWObject>(Memory.BM, BaseAddress);
        }

        public NpcObject ByName(string name)
        {
            foreach(NpcObject npc in NpcObjects)
            {
                if (npc.Name.Equals(name))
                    return npc;
            }

            throw new KeyNotFoundException();
        }
    }
}
