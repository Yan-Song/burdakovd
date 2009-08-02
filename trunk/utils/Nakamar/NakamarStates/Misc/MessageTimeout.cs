using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FiniteStateMachine;
using WoWMemoryManager;
using NakamarStates.Properties;
using System.Windows.Forms;

namespace NakamarStates
{
    public class MessageTimeout : State
    {
        DateTime LastMessageTime = DateTime.Now;
        int LastMessageId = -1;
        const int WaitMinutes = 10;

        public MessageTimeout(object machine, object memory) : base(machine, memory) { }

        public override int Priority
        {
            get { return int.MaxValue; }
        }

        public override bool NeedToRun
        {
            get
            {
                if (Memory.CurrentGameState != GameState.World)
                    return false;

                if (Memory.GetAddonMessage() != null)
                {
                    int id = Memory.GetAddonMessage().Id;
                    if (id != LastMessageId)
                    {
                        LastMessageId = id;
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
            Machine.DoNotRestart = true;
            Memory.StopWoW();
            Machine.StopEngineByWorker();
        }
    }
}
