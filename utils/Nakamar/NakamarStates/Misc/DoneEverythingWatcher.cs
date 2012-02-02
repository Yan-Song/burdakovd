using FiniteStateMachine;
using WLibrary;

namespace Plugins
{
    class DoneEverythingWatcher : State
    {
        public DoneEverythingWatcher(object machine, object memory)
            : base(machine, memory)
        {
        }

        public override int Priority
        {
            get { return 1100; }
        }

        public override bool NeedToRun
        {
            get
            {
                return
                    Memory.CurrentGameState == GameState.World &&
                    Memory.GetAddonMessage() != null &&
                    Memory.GetAddonMessage().doneEverything;
            }
        }

        public override void Run()
        {
            Log("Аддон сообщает, что сделал всё что мог на аукционе, можно останавливать бота");
            Machine.StopEngineByWorker();
        }
    }
}
