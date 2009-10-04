using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FiniteStateMachine;
using WoWMemoryManager;

namespace NakamarStates
{
    class WoWWindowActivator : State
    {
        // когда окно WoW было активно последний раз или когда была последняя попытка активации
        private DateTime lastActiveTime = DateTime.MinValue;

        // сколько времени должно пройти после lastActiveTime чтобы активировался этот модуль
        private static readonly TimeSpan limit = TimeSpan.FromSeconds(30);

        public WoWWindowActivator(object machine, object memory) : base(machine, memory)
        {

        }

        public override int Priority
        {
            get { return 10000; }
        }

        public override bool NeedToRun
        {
            get
            {
                if (Memory.IsWoWForeground())
                {
                    lastActiveTime = DateTime.Now;
                    return false;
                }
                else
                {
                    return DateTime.Now - lastActiveTime > limit; // не пора ли попытаться активировать окно WoW?
                }
            }
        }

        public override void Run()
        {
            lastActiveTime = DateTime.Now;
            Log("Активирую окно WoW");
            Memory.ActivateWoWWindow();
        }
    }
}
