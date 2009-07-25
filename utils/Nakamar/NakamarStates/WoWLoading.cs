using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FiniteStateMachine;
using WoWMemoryManager;


namespace NakamarStates
{
    public class WoWLoading : State
    {
        private long ClientConnectionLoadedTime = 0;
        private bool wasLoaded = false;

        public WoWLoading(object machine, object memory) : base(machine, memory) { }

        public override int Priority
        {
            get { return 1000000; }
        }

        public override bool NeedToRun
        {
            get
            {
                // надежда что за 20 секунд WoW запустится=)
                return DateTime.Now.Ticks - ClientConnectionLoadedTime < 200000000 //20s
                    || Memory.pClientConnection == 0 || ClientConnectionLoadedTime == 0;
                    
            }

        }

        public override void Run()
        {
            if (Memory.pClientConnection == 0)
                if (wasLoaded)
                {
                    Log("pClientConnection обнулён, похоже WoW закрывается, отключаю бота");
                    Machine.StopEngine();
                }
                else
                    ClientConnectionLoadedTime = DateTime.Now.Ticks;
            else
                if (!wasLoaded)
                {
                    if (ClientConnectionLoadedTime == 0)
                        ClientConnectionLoadedTime = DateTime.Now.Ticks;
                    wasLoaded = true;
                    Log("pClientConnection инициализирован, предположительно в течение " + 
                        "ближайших 20 сек WoW загрузится полностью");
                }
        }
    }
}
