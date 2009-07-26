using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FiniteStateMachine;
using WoWMemoryManager;
using System.Diagnostics;
using System.Threading;


namespace NakamarStates
{
    public class StartStopManager : State
    {
        private bool wasLoaded = false;

        public StartStopManager(object machine, object memory) : base(machine, memory) { }

        public override int Priority
        {
            get { return 1000000; }
        }

        public override bool NeedToRun
        {
            get
            {
                return !wasLoaded || Memory.pClientConnection == 0; 
            }

        }

        public override void Run()
        {
            // ждать пока WoW не запустится
            if (!wasLoaded)
            {
                Memory.WaitForInputIdle();
                Thread.Sleep(5000); // WaitForInputIdle() что-то рановато возвращается =(
                wasLoaded = true;
                Log("WoW полностью загрузился, можно приступать к работе");
            }

            else if (Memory.pClientConnection == 0)
            {
                Log("pClientConnection обнулён, похоже WoW закрывается, отключаю бота");
                Machine.StopEngine();
                Memory.StopWoW();
            }
        }
    }
}
