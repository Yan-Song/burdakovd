using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FiniteStateMachine;
using WoWMemoryManager;
using WLibrary;

namespace Plugins
{
    public class DoNotRestart : State
    {
        public DoNotRestart(object machine, object memory)
            : base(machine, memory)
        {

        }

        public override int Priority
        {
            get { return 1100; }
        }

        public override bool NeedToRun
        {
            get
            {
                return
                    Memory.CurrentGameState == GameState.World &&
                    Memory.GetAddonMessage() != null &&
                    string.IsNullOrEmpty(Memory.GetAddonMessage().DoNotRestart) == Machine.DoNotRestart;
            }
        }

        public override void Run()
        {
            if (!string.IsNullOrEmpty(Memory.GetAddonMessage().DoNotRestart))
            {
                Log("Аддон сообщает о проблеме: " + Memory.GetAddonMessage().DoNotRestart);
                Machine.DoNotRestart = true;
            }
            else
            {
                Log("Аларм отменяется");
                Machine.DoNotRestart = false;
            }
        }
    }
}
