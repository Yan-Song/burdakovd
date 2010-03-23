using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FiniteStateMachine;
using WoWMemoryManager;

namespace Plugins
{
    public class TimeOut : State
    {
        DateTime StartTime;
        static int WaitMinutes = 10;

        public TimeOut(object machine, object memory) : base(machine, memory)
        {
            StartTime = DateTime.Now;
        }

        public override int Priority
        {
            get { return int.MaxValue; }
        }

        public override bool NeedToRun
        {
            get
            {
                return (DateTime.Now - StartTime).TotalMinutes > WaitMinutes &&
                        Memory.GetAddonMessage() == null;
            }
        }

        public override void Run()
        {
            GameState g = Memory.CurrentGameState;

            Log("Прошло " + WaitMinutes +
                " минут с момента запуска бота, но до сих пор не удалось получить ни одного сообщения от аддона");
            if (g == GameState.Login)
                Log("  Не удалось залогиниться");
            else if (g == GameState.RealmWizard)
                Log("  Не удалось выбрать realm и получить список персонажей");
            else if (g == GameState.Character)
                Log("  Не удалось войти в игровой мир");
            else if (g == GameState.World && Memory.GetAddonMessage() == null)
            {
                Log("  Не удалось связаться с аддоном");
                Machine.DoNotRestart = true;
            }
            else
            {
                Log("  Произошло что-то непонятное");
                Machine.DoNotRestart = true;
            }

            Log("Закрываю WoW");
            Memory.StopWoW();
            Machine.StopEngineByWorker();
        }
    }
}
