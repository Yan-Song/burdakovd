using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WLibrary
{
    public interface GameMonitor
    {
        GameState CurrentGameState { get; }

        uint pClientConnection { get; }

        uint pObjectManager { get; }
    }
}
