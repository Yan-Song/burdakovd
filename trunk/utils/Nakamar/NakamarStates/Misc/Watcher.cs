using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FiniteStateMachine;
using WoWMemoryManager;
using Util;
using WoWMemoryManager.WoWObject;
using System.Collections;


namespace NakamarStates
{
    public class Watcher : State
    {
        private const bool Enabled = true;
        private Dictionary<string,string> current = new Dictionary<string,string>();
        private delegate string Getter(string key);

        public Watcher(object machine, object memory) : base(machine, memory) { }

        public override int Priority
        {
            get { return 50000; }
        }

        public override bool NeedToRun
        {
            get
            {
                if (Enabled)
                {
                    //Logger.Watch("CurrentGameState", Memory.CurrentGameState());
                    //Logger.Watch("Watcher", "CurrentState", Machine.CurrentState);
                    Logger.Watch("Watcher", "GetAddonMessage()", Memory.GetAddonMessage());
                    //Logger.Watch("Watcher", Memory.ObjectManager.Objects.

                    if (Memory.CurrentGameState == GameState.World)
                    {
                        //Logger.Watch("Watcher", "Objects.count", Memory.ObjectManager.Objects.Count());
                        //Logger.Watch("Watcher", "Players.count", Memory.ObjectManager.Players.Count());
                        //Logger.Watch("Watcher", "NPC.count", Memory.ObjectManager.NPC.Count());

                        //foreach (NpcObject npc in Memory.ObjectManager.NPC)
                        //    Logger.Watch("Watcher", "GUID:" + npc.Guid.ToString("X"), npc.ToString());
                    }

                }
                return false;
            }

        }

        public override void Run()
        {
            
        }
    }
}
