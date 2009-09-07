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
            firstObjectOffset = 0xAC,          // offset from the object manager to the first object // 3.1.3
            nextObjectOffset = 0x3C;           // offset from one object to the next // 3.1.3
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
            PlayerBaseOffset1 = 0x34, // 3.2.0
            PlayerBaseOffset2 = 0x24; // 3.2.0

        private BlackMagic Reader;
        public uint BaseAddress;               // the address off the object manager
        public IEnumerable<GameObject> GameObjects { get; private set; }
        public IEnumerable<WoWObject> Objects { get; private set; }
        public IEnumerable<NpcObject> NpcObjects { get; private set; }

        public PlayerObject LocalPlayer
        {
            get
            {
                uint p = Reader.ReadUInt(Patterns.PlayerBase);
                p = Reader.ReadUInt(p + PlayerBaseOffset1);
                p = Reader.ReadUInt(p + PlayerBaseOffset2);
                return new PlayerObject(Reader, p);
            }
        }

        public WoWObject ByGuid(ulong guid)
        {
            foreach(WoWObject w in new ObjectList<WoWObject>(Reader, BaseAddress))
                if(w.Guid == guid)
                    return w;
            throw new KeyNotFoundException("guid " + guid + " not found");
        }

        public ObjectManager(BlackMagic reader, uint objectManagerBaseAddress)
        {
            Reader = reader;
            BaseAddress = objectManagerBaseAddress;
            GameObjects = new ObjectList<GameObject>(Reader, BaseAddress);
            NpcObjects = new ObjectList<NpcObject>(Reader, BaseAddress);
            Objects = new ObjectList<WoWObject>(Reader, BaseAddress);
        }
    }
}
