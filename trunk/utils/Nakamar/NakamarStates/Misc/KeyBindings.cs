using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Input;

namespace Plugins
{
    public static class KeyBindings
    {
        public const Key
            // стандартные
            MoveForward = Key.W,
            TurnLeft = Key.A,
            TurnRight = Key.D,
            Jump = Key.Space,
            PrintScreen = Key.PrintScreen,

            // нестандартные
            SelectNearestFriend = Key.F1,
            Interact = Key.F2,
            MouseInteract = Key.F3,
            CameraZoomIn = Key.F6,
            CameraNormal = Key.F8,
            ConfirmPurchase = Key.F9;
    }
}
