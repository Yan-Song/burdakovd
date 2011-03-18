//
// burdakovd 2011 <kreved at kreved dot org>
//

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text.RegularExpressions;
using System.Threading;
using Util;
using WoWMemoryManager;

namespace FiniteStateMachine
{
    public class Engine
    {
        public ConfigWTF settings;

        /// <summary>
        /// сколько секунд ждать добровольного завершения worker
        /// </summary>
        private static int WaitWorkerForTerminate = 30;

        private Thread _workerThread;

        public Type CurrentState;
        
        private WoWMemoryManager.MemoryManager Memory;

        public Engine(WoWMemoryManager.MemoryManager memory, ConfigWTF settings)
        {
            this.settings = settings;
            DoNotRestart = false;

            States = new List<State>();
            Memory = memory;
        }

        public List<State> States { get; private set; }
        public bool Running { get; set; }
        public bool DoNotRestart { get; set; }
        public ulong FrameCount { get; private set; }

        /// <summary>
        /// Для блокировки FSM. Используется в Pulse() а также при любых обращениях 
        /// основного потока к FSM (кроме http://msdn.microsoft.com/en-us/library/aa691278(VS.71).aspx )
        /// состояния lock делать не должны, так как они вызываются из уже залоченной Pulse()
        /// 
        /// в StartEngine() блокировка не нужна, так как второго потока ещё нет
        /// 
        /// в StopEngine() тоже не нужна, так как все операции с States идут после уничтожения второго потока
        /// 
        /// перед вызовом ConfigureState() из главного потока блокировка непременно нужна
        /// </summary>
        readonly public Object Locker = new Object();

        /// <summary>
        /// для статистики
        /// </summary>
        readonly public Object Stats = new Object();

        public virtual void Pulse()
        {
            lock (Locker)
            {
                lock(Stats)
                    FrameCount++;

                // This starts at the highest priority state,
                // and iterates its way to the lowest priority.
                foreach (State state in States)
                {
                    if ((int)FrameCount % state.Frequency == 0)
                    {
                        if (state.NeedToRun)
                        {
                            lock(Stats)
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
        }

        private int neededFPS = 100;
        public void StartEngine(int framesPerSecond)
        {
            Running = true;
            neededFPS = framesPerSecond;
            // Leave it as a background thread. This CAN trail off
            // as the program exits, without any issues really.
            _workerThread = new Thread(Run) { IsBackground = true, Name = "FSM-worker" };
            _workerThread.Start();
        }

        private int sleepTime;
        private void Run()
        {
            try
            {
                sleepTime = 1000 / neededFPS;
                // This will immitate a games FPS
                // and attempt to 'pulse' each frame
                while (Running)
                {
                    AdjustSleepTime();
                    Pulse();
                    // Sleep for a 'frame'
                    Thread.Sleep(sleepTime);
                }
            }
            catch (Exception e)
            {
                Logger.LogError("FSM-worker", "Необработанное исключение в рабочем потоке");
                foreach(string line in Regex.Split(e.ToString(), Environment.NewLine))
                    Logger.Log("FSM-worker", " "+line);

                try
                {
                    Memory.KeyBoard.KeyUpAll();
                }
                catch
                {
                };

                Thread.Sleep(10000);
                try
                {
                    if (Memory.CurrentGameState == GameState.World)
                    {
                        Logger.LogError("FSM-worker", "В мире ошибок допускать нельзя, спалят. Запрещаю перезапуск");
                        DoNotRestart = true;
                    }
                }
                catch
                {
                    Logger.LogError("FSM-worker", "Ошибка при получении CurrentGameState. Запрещаю перезапуск");
                    DoNotRestart = true;
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

        private DateTime previousAdjustTime = DateTime.Now;
        private ulong previousFrameCount = 0;
        private void AdjustSleepTime()
        {
            double elapsed = (DateTime.Now - previousAdjustTime).TotalSeconds;

            if (elapsed < 1)
                return;

            previousAdjustTime = DateTime.Now;

            double realFPS = (FrameCount - previousFrameCount) / elapsed;

            previousFrameCount = FrameCount;

            int adj = 1;

            if (realFPS < neededFPS)
                sleepTime -= adj;
            else
                sleepTime += adj;

            if (sleepTime < 0)
                sleepTime = 0;
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
            if (_workerThread == null) // _workerThread используется только из основного потока
            {
                // Nothing to do.
                return;
            }

            // Make sure we let everyone know, we're not running anymore!
            Running = false; // атомарно

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

            // здесь остался только основной поток, так что можно делать всё что угодно
            foreach (State state in States)
            {
                state.Stop();
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
                throw new ApplicationException("Не удаётся загрузить состояния, имя файла null или \"\"");
            }

            // Make sure the file exists.
            if (!File.Exists(assemblyPath))
            {
                throw new ApplicationException("Не удаётся загрузить состояния из '" + assemblyPath + "': файл не найден");
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
                                States.Add(tempState);
                            }
                        }
                    }
                    catch (TargetInvocationException t)
                    {
                        Logger.LogError("FSM: " + type.Name, t.InnerException.Message);
                        Logger.LogError("FSM", type.Name + " не загружен");
                    }
                    catch (Exception ex)
                    {
                        Logger.LogError("FSM: " + type.Name, ex.Message);
                        Logger.LogError("FSM", type.Name + " не загружен");
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
