using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using FiniteStateMachine;
using NakamarStates.Properties;
using WoWMemoryManager;
using System.Windows.Input;
using System.Threading;

namespace NakamarStates
{
    public class ReLogger : State
    {
        private bool PasswordEntered = false;
        private bool LoggedIn = false;
        private bool CharacterSelected = false;
        private bool EnteredTheWorld = false;
        private bool RealmWizardMessagePrinted = false;

        public ReLogger(object machine, object memory) : base(machine, memory) { }

        public override void Configure()
        {
            lock (Settings.Default)
            {
                Relogger.PasswordDialog f = new Relogger.PasswordDialog();
                if (f.ShowDialog() == DialogResult.OK)
                {
                    Settings.Default.Password = f.PasswordBox.Text;
                    Log("Пароль изменён");
                }
                Settings.Default.Save();
            }
        }

        /// <summary>
        /// меньше чем WoWInBackground(10000)
        /// </summary>
        public override int Priority
        {
            get { return 5000; }
        }

        public override bool NeedToRun
        {
            get
            {
                return !EnteredTheWorld || Memory.CurrentGameState() != GameState.World;
            }
        }

        public override void Run()
        {
            GameState state = Memory.CurrentGameState();
            if (state == GameState.Login)
            {
                if (LoggedIn)
                {
                    Log("Дисконнект. Закрываю WoW.");
                    Machine.StopEngine();
                    Memory.StopWoW();
                }
                else if (!PasswordEntered)
                    EnterPassword();
            }
            else if (state == GameState.RealmWizard)
            {
                LoggedIn = true;
                if (!RealmWizardMessagePrinted)
                {
                    Log("Необходимо выбрать мир, сам я этого сделать не могу");
                    RealmWizardMessagePrinted = true;
                }
            }
            else if (state == GameState.Character)
            {
                LoggedIn = true;
                if (EnteredTheWorld)
                {
                    Log("Выкинуло из мира. Закрываю WoW.");
                    Machine.StopEngine();
                    Memory.StopWoW();
                }
                else if (!CharacterSelected)
                {
                    Log("Авторизация пройдена");
                    SelectCharacter();
                }
            }
            else if (state == GameState.World)
            {
                Log("Вхожу в игровой мир");
                LoggedIn = true;
                EnteredTheWorld = true;
            }
        }

        private void SelectCharacter()
        {
            Thread.Sleep(5000); // загрузка списка персонажей
            Memory.KB.PressKey(Key.Enter);
            CharacterSelected = true;
        }

        private void EnterPassword()
        {
            Memory.WaitForInputIdle();
            Log("Ввожу пароль");
            lock (Settings.Default) // Settings may be changed from main thread
            {
                Memory.KB.SendText(Settings.Default.Password);
            }
            Thread.Sleep(500); // на всякий случай
            Memory.KB.PressKey(Key.Enter);
            PasswordEntered = true;
        }
    }
}
