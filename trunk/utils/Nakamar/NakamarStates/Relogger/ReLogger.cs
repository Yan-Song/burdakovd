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
                throw new NotImplementedException();
            }
        }

        public override void Run()
        {
            throw new NotImplementedException();
        }

    }
}
