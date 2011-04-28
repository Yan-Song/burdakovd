using System.Threading;
using System.Windows.Input;
using FiniteStateMachine;
using WoWMemoryManager;

namespace Plugins
{
    public class ReLogger : State
    {
        public ReLogger(object machine, object memory) : base(machine, memory)
        {
        }

        public override int Priority
        {
            get { return 5000; }
        }

        public override bool NeedToRun
        {
            get
            {
                return Memory.CurrentGameState != GameState.World;
            }
        }

        public override void Run()
        {
            LogError("CurrentGameState == " + Memory.CurrentGameState + " != World. Дисконнект? Персонаж не залогинен?");
            LogError("Для работы персонаж должен быть залогинен и находиться в игровом мире");
            Machine.DoNotRestart = true;
            Machine.StopEngineByWorker();
        }
    }
}
