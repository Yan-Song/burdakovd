using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FiniteStateMachine;
using WoWMemoryManager;

namespace Plugins
{
    public class PurchaseConfirmation : State
    {
        DateTime nextPurchaseConfirmationTime = DateTime.Now;

        public PurchaseConfirmation(object machine, object memory) : base(machine, memory) { }

        public override int Priority
        {
            get { return 999; }
        }

        public override bool NeedToRun
        {
            get
            {
                return
                    DateTime.Now > nextPurchaseConfirmationTime
                    && Memory.IsWoWForeground()
                    && Memory.CurrentGameState == GameState.World
                    && Memory.GetAddonMessage() != null
                    && Memory.GetAddonMessage().NeedPurchaseConfirmation;
            }
        }

        public override void Run()
        {
            Memory.KeyBoard.PressKey(KeyBindings.ConfirmPurchase, false);
            nextPurchaseConfirmationTime = DateTime.Now + TimeSpan.FromMilliseconds((new Random()).Next(600, 1200));
        }
    }
}
