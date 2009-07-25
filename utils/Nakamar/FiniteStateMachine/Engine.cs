// 
// Copyright © ApocDev 2009 <apoc@apocdev.com>
//
 
// modified by burdakovd 2009 <kreved at kreved dot org>

using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using System.Threading;
using Util;

namespace FiniteStateMachine
{
    public class Engine
    {
        private Thread _workerThread;

        public Type LastState;
        
        private WoWMemoryManager.MemoryManager Memory;

        public Engine(WoWMemoryManager.MemoryManager memory)
        {
            
            States = new List<State>();
            Memory = memory;

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
                        LastState = state.GetType();
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
            if (!Running && _workerThread==null)
            {
                // Nothing to do.
                return;
            }

            // Make sure we let everyone know, we're not running anymore!
            Running = false;

            if (Thread.CurrentThread.ManagedThreadId == _workerThread.ManagedThreadId)
                return; // don't wait ourselves, Running = false is enough

            // ждём пока поток увидит что Running == false и завершится
            if (_workerThread.IsAlive)
                _workerThread.Join(1000);

            if (_workerThread.IsAlive)
            {
                Logger.Log("Рабочий поток FSM не завершился в течение одной секунды, убиваю");
                _workerThread.Abort();
                _workerThread.Join(); // ждём его завершения
                Logger.Log("Рабочий поток FSM убит");
            }
            
            // Clear out the thread object.
            _workerThread = null;
            
            
        }

        public void LoadState(State state)
        {
            if (!States.Contains(state))
            {
                States.Add(state);
                States.Sort();
            }
        }

        public void LoadStates(string assemblyPath)
        {
            // Make sure we actually have a path to work with.
            if (string.IsNullOrEmpty(assemblyPath))
            {
                return;
            }

            // Make sure the file exists.
            if (!File.Exists(assemblyPath))
            {
                return;
            }
            try
            {
                // Load the assembly, and get the types contained
                // within it.
                Assembly asm = Assembly.LoadFrom(assemblyPath);
                Type[] types = asm.GetTypes();

                foreach (Type type in types)
                {
                    // Here's some fairly simple stuff.
                    if (type.IsClass && type.IsSubclassOf(typeof(State)))
                    {
                        // Create the State using the Activator class.
                        var tempState = (State)Activator.CreateInstance(type, new object[] {this, Memory});
                        // Make sure we're not using two of the same state.
                        // (That would be bad!)
                        if (!States.Contains(tempState))
                        {
                            States.Add(tempState);
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                // Feel free to change this to some other logging method.
                Logger.LogError(ex.Message);
            }
        }
    }
}
