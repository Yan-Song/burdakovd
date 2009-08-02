using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Input;

namespace NakamarStates
{
    public static class KeyBindings
    {
        public static Key
            MoveForward = Key.W,
            TurnLeft = Key.A,
            TurnRight = Key.D,
            Jump = Key.Space,
            PrintScreen = Key.PrintScreen,
            RandomPet = Key.F4,
            ConfirmBuy = Key.F9,
            SelectNearestFriend = Key.F1,
            Interact = Key.F2,
            MouseInteract = Key.F3,
            CameraZoomIn = Key.F6,
            CameraZoomedIn = Key.F7,
            CameraNormal = Key.F8;
    }
}
