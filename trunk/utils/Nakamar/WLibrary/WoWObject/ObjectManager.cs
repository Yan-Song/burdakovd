using System.Collections;
using System.Collections.Generic;

namespace WLibrary
{
    public class ObjectManager
    {
        private class ObjectList<T> : IEnumerable<T> where T : WoWObject
        {
            private const uint
                firstObjectOffset = 0xC0,          // offset from the object manager to the first object
                nextObjectOffset = 0x3C;           // offset from one object to the next 
            private uint BaseAddress;
            private RawMemoryReader Reader;

            public ObjectList(RawMemoryReader reader, uint objectManagerBaseAddress)
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

        private const uint
            PlayerBaseOffset1 = 0x38,
            PlayerBaseOffset2 = 0x24;

        private RawMemoryReader reader;
        private PatternFinder patternFinder;
        private uint BaseAddress;

        public IEnumerable<GameObject> GameObjects { get; private set; }
        public IEnumerable<WoWObject> Objects { get; private set; }
        public IEnumerable<NpcObject> NpcObjects { get; private set; }

        public PlayerObject LocalPlayer
        {
            get
            {
                uint p = reader.ReadUInt(reader.ReadUInt(patternFinder.FindPattern(Patterns.PlayerBase)));
                p = reader.ReadUInt(p + PlayerBaseOffset1);
                p = reader.ReadUInt(p + PlayerBaseOffset2);
                return new PlayerObject(reader, p);
            }
        }

        public WoWObject ByGuid(ulong guid)
        {
            foreach(WoWObject w in new ObjectList<WoWObject>(reader, BaseAddress))
                if(w.Guid == guid)
                    return w;

            throw new KeyNotFoundException("guid " + guid + " not found");
        }

        public ObjectManager(RawMemoryReader reader_, PatternFinder patternFinder_, uint objectManagerBaseAddress)
        {
            reader = reader_;
            patternFinder = patternFinder_;
            BaseAddress = objectManagerBaseAddress;
            GameObjects = new ObjectList<GameObject>(reader, BaseAddress);
            NpcObjects = new ObjectList<NpcObject>(reader, BaseAddress);
            Objects = new ObjectList<WoWObject>(reader, BaseAddress);
        }

        public NpcObject ByName(string name)
        {
            foreach(NpcObject npc in NpcObjects)
            {
                if (npc.Name.Equals(name))
                {
                    return npc;
                }
            }

            throw new KeyNotFoundException();
        }
    }
}
