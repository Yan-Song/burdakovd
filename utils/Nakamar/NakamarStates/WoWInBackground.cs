using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FiniteStateMachine;
using WoWMemoryManager;
using Util;


namespace NakamarStates
{
    public class WoWInBackground : State
    {
        public WoWInBackground(object machine, object memory) : base(machine, memory) { }

        public override int Priority
        {
            get { return 10000; }
        }

        public override bool NeedToRun
        {
            get
            {
                return !Memory.IsWoWForeground();
            }

        }

        public override void Run()
        {
            // отпустить все клавиши если нажаты, но при отпускании не посылать сообщения в WoW
        }
    }
}
