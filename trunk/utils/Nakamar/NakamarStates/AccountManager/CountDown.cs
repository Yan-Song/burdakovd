using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Plugins.Properties;

namespace Plugins.AccountManager
{
    public partial class CountDown : Form
    {
        public bool SettingsModified { get; private set; }
        private int secondsLeft = 10;

        public CountDown()
        {
            InitializeComponent();
            SettingsModified = false;
            updateGuiTime();
        }

        private void Options_Click(object sender, EventArgs e)
        {
            SettingsModified = true;
            CountDownTimer.Enabled = false;
            Hide();
            new ProfileManagement().ShowDialog();
            Settings.Default.Save();
            Close();
        }

        /// <summary>
        /// обновить надпись на кнопке
        /// </summary>
        private void updateGuiTime()
        {
            if (CountDownTimer.Enabled)
            {
                OK.Text = string.Format("OK ({0:d})", secondsLeft);
            }
            else
            {
                OK.Text = "OK";
            }
            
        }

        private void CountDownTimer_Tick(object sender, EventArgs e)
        {
            --secondsLeft;

            updateGuiTime();

            if (secondsLeft <= 0)
            {
                Close();
            }
        }

        public void SetText(string[] text)
        {
            MessageBox.Lines = text;
        }

        private void doNotShowThisWindow_CheckedChanged(object sender, EventArgs e)
        {
            CountDownTimer.Enabled = false;
            updateGuiTime();
        }

        private void MessageBox_Enter(object sender, EventArgs e)
        {
            CountDownTimer.Enabled = false;
            updateGuiTime();
        }
    }
}
