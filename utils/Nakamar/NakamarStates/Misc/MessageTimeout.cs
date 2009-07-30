using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FiniteStateMachine;
using WoWMemoryManager;
using NakamarStates.Properties;
using System.Windows.Forms;

namespace NakamarStates
{
    public class MessageTimeout : State
    {
        DateTime LastMessageTime = DateTime.Now;
        int LastMessageId = -1;
        const int WaitMinutes = 5;

        public MessageTimeout(object machine, object memory) : base(machine, memory) { }

        public override void Configure()
        {
            DialogResult result = MessageBox.Show("Этот модуль будет выключать бота если в течение " +
                WaitMinutes + " минут не получено ни одного сообщения от аддона " + Environment.NewLine +
                "Включить?", "Включить MessageTimeout?",
                MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question);
            if (result == DialogResult.Yes)
            {
                Settings.Default.EnableMessageTimeout = true;
                Log("Включён");
            }
            else if(result == DialogResult.No)
            {
                Settings.Default.EnableMessageTimeout = false;
                Log("Отключён");
            }
            Settings.Default.Save();
        }

        public override int Priority
        {
            get { return int.MaxValue; }
        }

        public override bool NeedToRun
        {
            get
            {
                if (!Settings.Default.EnableMessageTimeout)
                    return false;

                if (Memory.CurrentGameState != GameState.World)
                    return false;

                if (Memory.GetAddonMessage() != null)
                {
                    int id = Memory.GetAddonMessage().id;
                    if (id != LastMessageId)
                    {
                        LastMessageId = id;
                        LastMessageTime = DateTime.Now;
                    }
                }

                return (DateTime.Now - LastMessageTime).TotalMinutes > WaitMinutes;
            }
        }

        public override void Run()
        {
            Log("За последние " + WaitMinutes + " минут не получено ни одного сообщения от аддона");
            Log("Выключаю WoW");
            Memory.StopWoW();
            Machine.StopEngineByWorker();
        }
    }
}
