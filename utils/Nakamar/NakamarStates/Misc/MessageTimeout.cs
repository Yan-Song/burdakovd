using System;
using FiniteStateMachine;
using WoWMemoryManager;
using WLibrary;

namespace Plugins
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
