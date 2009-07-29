using System;
using FiniteStateMachine;
using WoWMemoryManager;

namespace NakamarStates
{
    public class MessageScanner : State
    {

        DateTime nextScan;
        static int WaitSeconds = 60;

        public MessageScanner(object machine, object memory) : base(machine, memory)
        {
            nextScan = DateTime.Now;
        }

        public override int Priority
        {
            get { return 0; }
        }

        public override bool NeedToRun
        {
            get
            {
                return DateTime.Now > nextScan && Memory.CurrentGameState==GameState.World &&
                    Memory.GetAddonMessage(false) == null;
            }
        }

        public override void Run()
        {
            Log("Поиск сигнатуры аддона...");
            if(Memory.RescanAddonMessage()==null)
                Log("Не найдено. Повтор через " + WaitSeconds + " сек.");
            nextScan = DateTime.Now + TimeSpan.FromSeconds(WaitSeconds);
        }
    }
}
