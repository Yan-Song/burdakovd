﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Nakamar
{
    public partial class MainForm : Form
    {
        private bool BotEnabled = false;


        public MainForm()
        {
            InitializeComponent();
        }

        private void SaveSettings()
        {
            Properties.Settings.Default.Save();
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            SaveSettings();
        }
        
        private void SaveSettings(object sender, EventArgs e)
        {
            SaveSettings();
        }

        private void Log(string s)
        {
            LogBox.Items.Add("[" + DateTime.Now.ToLongTimeString() + "] " + s);
            if(AutoScrollCheckBox.Checked)
                LogBox.TopIndex = LogBox.Items.Count - 1;
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            UpdateBotStateGUI();
            Log("Программа запущена");
        }

        /// <summary>
        /// обновляет доступность кнопок включения и выключения бота
        /// </summary>
        private void UpdateBotStateGUI()
        {
            EnableBotButton.Enabled = !BotEnabled;
            DisableBotButton.Enabled = BotEnabled;
            BotStateLabel.Text = BotEnabled ? "Бот включён" : "Бот выключен";
        }

        private void EnableBot(object sender, EventArgs e)
        {
            EnableBot();
        }

        private void EnableBot()
        {

            throw new NotImplementedException();
        }

        private void DisableBot(object sender, EventArgs e)
        {
            DisableBot();
        }

        private void DisableBot()
        {
            throw new NotImplementedException();
        }

        private void ClearLog(object sender, EventArgs e)
        {
            LogBox.Items.Clear();
        }
    }
}
