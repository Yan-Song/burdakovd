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
using System.Text.RegularExpressions;

namespace FiniteStateMachine
{
    public class Engine
    {
        /// <summary>
        /// сколько секунд ждать добровольного завершения worker
        /// </summary>
        private static int WaitWorkerForTerminate = 3;

        private Thread _workerThread;

        public Type CurrentState;
        
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
        public bool Running { get; set; }
        public bool DoNotRestart { get; set; }
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
                        CurrentState = state.GetType();
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
            _workerThread = new Thread(Run) { IsBackground = true, Name = "FSM-worker" };
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
            catch (Exception e)
            {
                DoNotRestart = true;
                Logger.LogError("FSM-worker", "Необработанное исключение в рабочем потоке");
                foreach(string line in Regex.Split(e.ToString(), Environment.NewLine))
                    Logger.Log("FSM-worker", " "+line);
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

        /// <summary>
        /// call only by worker thread
        /// </summary>
        public void StopEngineByWorker()
        {
            Running = false;
        }

        /// <summary>
        /// call only from main thread
        /// </summary>
        public void StopEngine()
        {
            if (!Running && _workerThread == null)
            {
                // Nothing to do.
                return;
            }

            // Make sure we let everyone know, we're not running anymore!
            Running = false;

            // ждём пока поток увидит что Running == false и завершится
            if (_workerThread.IsAlive)
                _workerThread.Join(WaitWorkerForTerminate * 1000);

            if (_workerThread.IsAlive)
            {
                Logger.LogError("FSM", "Рабочий поток не завершился в течение " + WaitWorkerForTerminate + " секунд, убиваю");
                _workerThread.Abort();
                if (_workerThread.Join(1000))
                    Logger.Log("FSM", "Рабочий поток убит");
                else
                    throw new Exception("Не удалось убить поток. Крайне рекомендуется перезапустить программу");
            }

            foreach (State state in States)
                state.Stop();

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
                    try
                    {
                        // Here's some fairly simple stuff.
                        if (type.IsClass && type.IsSubclassOf(typeof(State)))
                        {
                            // Create the State using the Activator class.
                            var tempState = (State)Activator.CreateInstance(type, new object[] { this, Memory });
                            // Make sure we're not using two of the same state.
                            // (That would be bad!)
                            if (!States.Contains(tempState))
                            {
                                //Logger.Log("loading "+tempState.GetType().Name);
                                States.Add(tempState);
                            }
                        }
                    }
                    catch (TargetInvocationException t)
                    {
                        Logger.LogError("FSM: " + type.Name, t.InnerException.Message);
                    }
                    catch (Exception ex)
                    {
                        Logger.LogError("FSM: " + type.Name, ex.Message);
                    }
                }
            }
            catch (Exception ex)
            {
                Logger.LogError("FSM", ex.Message);
            }
        }
    }
}
