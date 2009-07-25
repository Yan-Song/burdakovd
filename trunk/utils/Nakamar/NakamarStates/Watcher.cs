using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FiniteStateMachine;
using WoWMemoryManager;
using Util;


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
                    Logger.Watch("CurrentGameState", Memory.CurrentGameState().ToString());
                }
                return false;
            }

        }

        public override void Run()
        {
            
        }
    }
}
