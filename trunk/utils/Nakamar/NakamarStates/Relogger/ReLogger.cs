using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using FiniteStateMachine;
using NakamarStates.Properties;
using WoWMemoryManager;

namespace NakamarStates
{
    public class ReLogger : State
    {
        private bool EnteredPasword = false;
        private bool LoggedIn = false;
        private bool SelectedCharacter = false;
        private bool EnteredTheWorld = false;

        public ReLogger(object machine, object memory) : base(machine, memory) { }

        public override void Configure()
        {
            Relogger.PasswordDialog f = new Relogger.PasswordDialog();
            if (f.ShowDialog() == DialogResult.OK)
            {
                Settings.Default.Password = f.PasswordBox.Text;
                Log("Пароль изменён");
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
                    Log("Дисконнект");
                    Machine.StopEngine();
                }
                else if (!EnteredPasword)
                    EnterPassword();
                else
                    Memory.WaitForInputIdle(); // ждать пока не залогинится
            }
            else if (state == GameState.Character)
            {
                LoggedIn = true;
                if (EnteredTheWorld)
                {
                    Log("Выкинуло из мира");
                    Machine.StopEngine();
                }
                else if (!SelectedCharacter)
                {
                    Log("Авторизация прйдена");
                    SelectCharacter();
                }
                else
                    Memory.WaitForInputIdle(); // ждать пока не зайдёт в мир
            }
            else if (state == GameState.World)
            {
                Log("Вошёл в игровой мир");
                EnteredTheWorld = true;
            }
        }

        private void SelectCharacter()
        {
            // Memory.SendKeys(Enter);
            throw new NotImplementedException();
        }

        private void EnterPassword()
        {
            lock (this) // Settings may be changed from main thread
            {
                Memory.SendKeys(Settings.Default.Password);
            }
            // Memory.SendKeys(Enter);
            throw new NotImplementedException();
        }

    }
}
