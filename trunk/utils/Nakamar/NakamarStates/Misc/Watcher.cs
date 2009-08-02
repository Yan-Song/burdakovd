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
                    //Logger.Watch("Watcher", "GetAddonMessage()", Memory.GetAddonMessage());
                    //Logger.Watch("Watcher", Memory.ObjectManager.Objects.

                    if (Memory.CurrentGameState == GameState.World)
                    {
                        /*PlayerObject player = Memory.ObjectManager.LocalPlayer;*/
                        /*Logger.Watch("Watcher", "LocalPlayer",
                            "XYZ(" + player.XPosition + "; " + player.YPosition + "; " + player.ZPosition +
                            "), rotation: " + player.Rotation);*/
                        //Logger.Watch("Watcher", "Player.Guid", player.Guid);
                        //Logger.Watch("Watcher", "Target name", Memory.TargetName);
                        /*try
                        {
                            CreatureObject target = Memory.ObjectManager.ByGuid(player.TargetGuid) as CreatureObject;
                            Logger.Watch("Watcher", "target", "XYZ(" + target.XPosition + "; " + target.YPosition + "; " + target.ZPosition +
                            "), rotation: " + target.Rotation);
                            
                        }
                        catch (KeyNotFoundException)
                        {
                            Logger.Watch("Watcher", "target", "target not found (" + player.TargetGuid + ")");
                        }*/
                        //Logger.Watch("Watcher", "Player.Guid2", player.Guid2);
                        /*foreach (WoWObject o in Memory.ObjectManager.Objects)
                            Logger.Watch("Watcher", o.ToString(), "Type is " + o.Type + ", Name is " + o.Name);*/
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
