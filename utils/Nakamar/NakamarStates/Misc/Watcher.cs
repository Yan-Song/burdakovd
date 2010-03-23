using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FiniteStateMachine;
using WoWMemoryManager;
using Util;
using WoWMemoryManager.WoWObject;
using System.Collections;


namespace Plugins
{
    public class Watcher : State
    {
        private const bool Enabled = false;
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
                    // something
                }
                return false;
            }
        }

        public override void Run()
        {
            
        }
    }
}
