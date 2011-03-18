using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FiniteStateMachine;
using WoWMemoryManager;

namespace Plugins
{
    public class RandomPet : State
    {
        //DateTime lastRandomPetDecisionTime = DateTime.Now;

        public RandomPet(object machine, object memory) : base(machine, memory) { }

        public override int Priority
        {
            get { return 999; }
        }

        public override bool NeedToRun
        {
            get
            {
                return false;
                    //(DateTime.Now - lastRandomPetDecisionTime).TotalSeconds > 1
                    //&& Memory.CurrentGameState == GameState.World;
            }
        }

        public override void Run()
        {
            /*lastRandomPetDecisionTime = DateTime.Now;
            if ((new Random()).Next(1, 1200) == 1)
                Memory.KeyBoard.PressKey(KeyBindings.RandomPet, false);*/
        }

    }
}
