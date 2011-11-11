
namespace WLibrary
{
    public interface GameMonitor
    {
        GameState CurrentGameState { get; }

        uint pClientConnection { get; }

        uint pObjectManager { get; }
    }
}
