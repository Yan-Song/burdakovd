// 
// Copyright © ApocDev 2009 <apoc@apocdev.com>
// 
// modified 

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using System.Threading;
using Nakamar;

namespace FiniteStateMachine
{
    public class Engine
    {
        private Thread _workerThread;

        public Engine()
        {
            States = new List<State>();

            // Remember: We implemented the IComparer, and IComparable
            // interfaces on the State class!
            States.Sort();
        }

        public List<State> States { get; private set; }
        public bool Running { get; private set; }
        public ulong FrameCount { get; private set; }

        public virtual void Pulse()
        {
            FrameCount++;

            // This starts at the highest priority state,
            // and iterates its way to the lowest priority.
            foreach (State state in States)
            {
                if ((int)FrameCount % state.Frequency == 0)
                {
                    if (state.NeedToRun)
                    {
                        state.Run();
                        // Break out of the iteration,
                        // as we found a state that has run.
                        // We don't want to run any more states
                        // this time around.
                        break;
                    }
                }
            }
        }

        public void StartEngine(int framesPerSecond)
        {
            // We want to round a bit here.
            int sleepTime = 1000 / framesPerSecond;

            Running = true;

            // Leave it as a background thread. This CAN trail off
            // as the program exits, without any issues really.
            _workerThread = new Thread(Run) { IsBackground = true };
            _workerThread.Start(sleepTime);
        }

        private void Run(object sleepTime)
        {
            try
            {
                // This will immitate a games FPS
                // and attempt to 'pulse' each frame
                while (Running)
                {
                    Pulse();
                    // Sleep for a 'frame'
                    Thread.Sleep((int)sleepTime);
                }
            }
            finally
            {
                // If we exit due to some exception,
                // that isn't caught elsewhere,
                // we need to make sure we set the Running
                // property to false, to avoid confusion,
                // and other bugs.
                Running = false;
            }
        }

        public void StopEngine()
        {
            if (!Running)
            {
                // Nothing to do.
                return;
            }
            if (_workerThread.IsAlive)
            {
                _workerThread.Abort();
            }
            // Clear out the thread object.
            _workerThread = null;
            // Make sure we let everyone know, we're not running anymore!
            Running = false;
        }

        //public void 
    }
}
