using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FiniteStateMachine;

namespace NakamarStates
{
    class MessageTimeout : State
    {
        DateTime LastMessageTime;
        int LastMessageId = -1;
        const int WaitMinutes = 5;

        public override int Priority
        {
            get { return int.MaxValue; }
        }

        public override bool NeedToRun
        {
            get
            {
                if (Memory.GetAddonMessage() != null)
                {
                    int id = Memory.GetAddonMessage().id;
                    if (id != LastMessageId)
                    {
                        LastMessageId = Memory.GetAddonMessage().id;
                        LastMessageTime = DateTime.Now;
                    }
                }

                return (DateTime.Now - LastMessageTime).TotalMinutes > WaitMinutes;
            }
        }

        public override void Run()
        {
            Log("За последние " + WaitMinutes + " минут не получено ни одного сообщения от аддона");
            Log("Выключаю WoW");
            Memory.StopWoW();
            Machine.StopEngineByWorker();
        }
    }
}
