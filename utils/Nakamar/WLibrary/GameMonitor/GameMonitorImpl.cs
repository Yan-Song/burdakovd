using System;

namespace WLibrary
{
    public class GameMonitorImpl : GameMonitor
    {
        private RawMemoryReader reader;
        private PatternFinder finder;

        public GameMonitorImpl(RawMemoryReader reader_, PatternFinder finder_)
        {
            reader = reader_;
            finder = finder_;
        }

        public GameState CurrentGameState
        {
            get
            {
                try
                {
                    uint gameStateIdPtr = reader.ReadUInt(finder.FindPattern(Patterns.GameStateId));
                    uint gameStateId = reader.ReadUInt(gameStateIdPtr);
                    uint gameStateStringRepresentationsBase = reader.ReadUInt(finder.FindPattern(Patterns.GameStateStringRepresentationBase));
                    string state = reader.ReadASCIIString(reader.ReadUInt(gameStateStringRepresentationsBase + 4 * gameStateId), 100);

                    if (state == "login")
                        return GameState.Login;

                    else if (state == "realmwizard")
                        return GameState.RealmWizard;

                    else if (state == "charselect")
                        if (pObjectManager == 0)
                            return GameState.Character;
                        else
                            return GameState.World;

                    else if (state == "")
                        return GameState.None;

                    else
                        throw new Exception("Unknown GameState: " + state);
                }
                catch (Exception)
                {
                    return GameState.None;
                }
            }
        }

        public uint pClientConnection
        {
            get { return reader.ReadUInt(reader.ReadUInt(finder.FindPattern(Patterns.ClientConnection))); }
        }

        public uint pObjectManager
        {
            get { return reader.ReadUInt(pClientConnection + reader.ReadUInt(finder.FindPattern(Patterns.ObjectManagerOffset))); }
        }
    }
}
