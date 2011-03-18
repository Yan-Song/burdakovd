using System;
using System.Diagnostics;
using System.IO;
using System.Threading;
using FiniteStateMachine;
using Util;
using WoWMemoryManager;

namespace NakamarConsole
{
    class Program
    {
        /// <summary>
        /// Служит для синхронизации потоков логирования
        /// </summary>
        static Object sync = new Object();

        static void Main(string[] args)
        {
            if (args.Length == 0)
            {
                Console.WriteLine(String.Format("usage:\n  {0} <config_file> [<wow_process_id>]\n" + 
                    "  Если wow_process_id=-1 или отсутствует, то будет выбран произвольный процесс WoW.", System.AppDomain.CurrentDomain.FriendlyName));
                Environment.Exit(1);
            }

            try
            {
                doMain(args);
            }
            catch(Exception ex) {
                Console.WriteLine("Failure!");
                Console.WriteLine(ex);
                Environment.Exit(-1);
            }
        }

        private static void doMain(string[] args)
        {
            // направляем логирование в консоль
            Logger.RawLog = Console.WriteLine;

            // загружаем настройки
            ConfigWTF settings = new ConfigWTF(args[0]);
            Logger.Log("Main", "Loaded settings from " + args[0]);

            // делаем логирование ещё и в файл
            string logFileName = settings["logDirectory"] +
                Path.DirectorySeparatorChar + DateTime.Now.ToString("yyyyMMdd.HHmmss") +
                "." + Process.GetCurrentProcess().Id + ".log";
            TextWriter logFile = new StreamWriter(logFileName);

            // чтобы можно было писать из нескольких потоков
            Logger.RawLog = delegate(string message)
            {
                lock (sync)
                {
                    Console.WriteLine(message);
                    logFile.WriteLine(message);
                    logFile.Flush();
                }
            };

            Logger.Log("Main", "Лог пишется в " + logFileName);

            Console.CancelKeyPress += delegate
            {
                Logger.Log("Ctrl-C", "Прервано из консоли");
            };

            // запускаем бота
            int exitCode = startBot(args.Length > 1 ? Int32.Parse(args[1]) : -1, settings);
            Environment.Exit(exitCode);
        }

        private static int chooseAnyWoW()
        {            
            foreach (Process p in Process.GetProcessesByName("wow"))
                if (p.MainWindowTitle == "World of Warcraft")
                    return p.Id;

            Logger.LogError("chooseAnyWoW", "не найдено ни одного процесса WoW");
            Environment.Exit(1);
            return -1;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="pid"></param>
        /// <param name="settings"></param>
        /// <returns>код возврата</returns>
        private static int startBot(int pid, ConfigWTF settings)
        {
            // подготовка

            int WoWPid = pid == -1 ? chooseAnyWoW() : pid;

            MemoryManager memoryManager = new MemoryManager(WoWPid);

            Engine FSM = new Engine(memoryManager, settings);

            string pluginsPath = System.IO.Path.GetDirectoryName(Process.GetCurrentProcess().MainModule.FileName) + Path.DirectorySeparatorChar + "Plugins.dll";
            Logger.Log("startBot", "Загружаю плагины из " + pluginsPath);
            FSM.LoadStates(pluginsPath);
            FSM.States.Sort();

            // собственно запуск
            FSM.StartEngine(Int32.Parse(settings["FPS"]));

            Logger.Log("startBot", "Бот запущен, WoW process id: " + WoWPid + ", загружено состояний: " + FSM.States.Count);

            // ждём пока FSM остановится и показываем в Title статус
            ulong PreviousFrameCount = 0;
            while (FSM.Running)
            {
                lock (FSM.Stats)
                {
                    AddonMessage message = memoryManager.GetAddonMessage();
                    Console.Title =
                        "FPS: " + (FSM.FrameCount - PreviousFrameCount) +
                        " | Bot: " + ((FSM.CurrentState == null) ? "запускается" : FSM.CurrentState.Name) +
                        " | Addon: " + (message == null ? "null" : message.CurrentState);
                    PreviousFrameCount = FSM.FrameCount;
                }

                Thread.Sleep(1000);
            }

            // проверка результата
            Logger.Log("startBot", String.Format("Бот остановлен: аварийно = {0}", FSM.DoNotRestart));
            return FSM.DoNotRestart ? 1 : 0;
        }
    }
}
