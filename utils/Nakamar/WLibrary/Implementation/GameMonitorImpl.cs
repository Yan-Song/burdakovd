using System;
using System.Collections.Generic;

namespace WLibrary
{
    public class GameMonitorImpl : GameMonitor
    {
        private RawMemoryReader reader;
        private PatternFinder finder;

        private HashSet<string> reportedErrors = new HashSet<string>();
        private Action<string> LogError;

        public GameMonitorImpl(RawMemoryReader reader_, PatternFinder finder_, Action<string> errorLogger_)
        {
            reader = reader_;
            finder = finder_;
            LogError = errorLogger_;
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
                        throw new Exception("Unknown GameState: <empty string>");

                    else
                        throw new Exception("Unknown GameState: " + state);
                }
                catch (Exception ex)
                {
                    string message = ex.ToString();

                    if (!reportedErrors.Contains(message))
                    {
                        LogError("Failed to get game state, returning GameState.None. Description below (each failure is reported only once)" 
                            + Environment.NewLine + message);
                        reportedErrors.Add(message);
                    }

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
