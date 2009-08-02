using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FiniteStateMachine;
using WoWMemoryManager;

namespace NakamarStates
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
                    Memory.GetAddonMessage().DoNotRestart != "";
            }
        }

        public override void Run()
        {
            Log("Аддон попросил не перезапускать WoW (" + Memory.GetAddonMessage().DoNotRestart + ")");
            Machine.DoNotRestart = true;
            Machine.StopEngineByWorker();
        }
    }
}
