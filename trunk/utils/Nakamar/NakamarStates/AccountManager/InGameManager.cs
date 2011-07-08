using System;
using FiniteStateMachine;
using WoWMemoryManager;
using WLibrary;

namespace Plugins.AccountManager
{
    public class InGameManager : State
    {
        bool warned = false;

        public InGameManager(object machine, object memory)
            : base(machine, memory)
        {

        }

        public override int Priority
        {
            get { return 1000; }
        }

        /// <summary>
        /// проверяет, вдруг аддону нечего делать
        /// </summary>
        public override bool NeedToRun
        {
            get
            {
                // работаем только в мире
                if (Memory.CurrentGameState != GameState.World)
                {
                    return false;
                }

                if (Memory.GetAddonMessage() != null)
                {
                    if (Memory.GetAddonMessage().NothingToDo)
                    {
                        string key = "exitWhenNothingToDo";
                        if(!warned && Machine.settings.ContainsKey(key)) {
                            Log("[Warning] параметр " + key + " игнорируется, бот НЕ выходит");
                            warned = true;
                        }
                        return false;
                    }
                }

                return false;
            }
        }

        public override void Run()
        {
            Log("Аддону нечего делать. Закрываю WoW, останавливаю бота.");
            Memory.StopWoW();
            Machine.StopEngineByWorker();
        }
    }
}
