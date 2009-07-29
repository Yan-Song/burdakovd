using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FiniteStateMachine;
using WoWMemoryManager;

namespace NakamarStates
{
    /// <summary>
    /// Это состояние обладает наименьшим приоритетом
    /// </summary>
    public class Idle : State
    {
        public Idle(object machine, object memory) : base(machine, memory) { }

        public override int Priority
        {
            get { return int.MinValue; }
        }

        public override bool NeedToRun
        {
            get { return true; }
        }

        public override void Run()
        {
            return;
        }

    }
}
