﻿using System;
using FiniteStateMachine;
using WoWMemoryManager;
using WLibrary;

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
                    && Memory.CurrentGameState == GameState.World
                    && Memory.GetAddonMessage() != null
                    && Memory.GetAddonMessage().NeedPurchaseConfirmation;
            }
        }

        public override void Run()
        {
            Memory.KeyBoard.PressKey(KeyBindings.ConfirmPurchase, false);
            Log("Sent confirmation: " + KeyBindings.ConfirmPurchase);
            nextPurchaseConfirmationTime = DateTime.Now + TimeSpan.FromMilliseconds((new Random()).Next(600, 1200));
        }
    }
}
