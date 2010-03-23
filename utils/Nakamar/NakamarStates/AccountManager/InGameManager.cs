using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FiniteStateMachine;
using WoWMemoryManager;
using Plugins.Properties;

namespace Plugins.AccountManager
{
    public class InGameManager : State
    {
        DateTime lastSessionUpdate = DateTime.MinValue;
        string CurrentAddonState, PreviousAddonState;

        public InGameManager(object machine, object memory)
            : base(machine, memory)
        {

        }

        public override int Priority
        {
            get { return 1000; }
        }

        /// <summary>
        /// проверяет
        /// 1) каждую минуту обновляет текущую сессию
        /// 2) а также проверяет, вдруг аддону нечего делать
        /// 3) проверяет, не нужно ли закрыть WoW, чтоб потом зайти другим аккаунтом
        /// </summary>
        public override bool NeedToRun
        {
            get
            {
                // работаем только в мире
                if (Memory.CurrentGameState != GameState.World)
                {
                    return false;
                }

                // обновить сессию
                if ((DateTime.Now - lastSessionUpdate).TotalMinutes >= 1)
                {
                    lastSessionUpdate = DateTime.Now;
                    Settings.Default.Profiles[Settings.Default.CurrentProfile].UpdateSession();
                    Settings.Default.Save();
                }

                if (Memory.GetAddonMessage() != null)
                {
                    string state = Memory.GetAddonMessage().CurrentState;

                    PreviousAddonState = CurrentAddonState;
                    CurrentAddonState = state;

                    if (CurrentAddonState == "SCANNING")
                    {
                        // NTD
                        if (CurrentAddonState != PreviousAddonState)
                        {
                            Settings.Default.Profiles[Settings.Default.CurrentProfile].NothingToDo();
                            Settings.Default.Save();
                        }

                        return CheckIfNeedToLogout();
                    }
                }

                return false;
            }
        }

        private bool CheckIfNeedToLogout()
        {
            string best = AccountManager.Manager.GetBestProfile();

            if (!string.IsNullOrEmpty(best))
            {
                // есть кандидат на логин
                return Settings.Default.Profiles[best].SinceLastNothingToDo().TotalHours > (double)Settings.Default.HowOldHoursNTDIsInteresting;
            }
            else
            {
                return false;
            }
        }

        public override void Run()
        {
            Log("Пора зайти под другим профилем. Закрываю WoW.");
            Memory.StopWoW();
            Machine.StopEngineByWorker();
        }

        public override void Stop()
        {
            if (Machine.DoNotRestart)
            {
                Settings.Default.Profiles[Settings.Default.CurrentProfile].Enabled = false;
                Settings.Default.Save();

                Log("Произошла какая-то ошибка, отключаю текущий профиль");
            }
        }
    }
}
