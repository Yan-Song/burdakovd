using System;
using FiniteStateMachine;
using WoWMemoryManager;

namespace NakamarStates
{
    public class MessageScanner : State
    {

        DateTime nextScan;
        static int WaitSeconds = 20;

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
            try
            {
                if (Memory.RescanAddonMessage() == null)
                    Log("Не найдено. Повтор через " + WaitSeconds + " сек.");
            }
            catch (Exception ex)
            {
                if (ex.Message == "ReadUInt failed.")
                    Log("ReadUInt failed при поиске сигнатуры. Повтор через " + WaitSeconds + " сек.");
                else
                    throw;
            }
            nextScan = DateTime.Now + TimeSpan.FromSeconds(WaitSeconds);
        }
    }
}
