
namespace WLibrary
{
    public interface GameMonitor : GameStateMonitor
    {
        uint pClientConnection { get; }

        uint pObjectManager { get; }
    }
}
