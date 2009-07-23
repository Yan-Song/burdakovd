using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Nakamar
{
    public partial class MainForm : Form
    {
        private bool BotEnabled = false;
        IntPtr WoWHandle;


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

        private void Log(string text)
        {
            LogBox.Items.Add("[" + DateTime.Now.ToLongTimeString() + "] " + text);
            if(AutoScrollCheckBox.Checked)
                LogBox.TopIndex = LogBox.Items.Count - 1;
        }

        private void LogError(string text)
        {
            Log("Ошибка: "+text);
        }

        /// <summary>
        /// некоторая инициализация
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MainForm_Load(object sender, EventArgs e)
        {
            Process.EnterDebugMode();
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

        private void EnableBotByUser(object sender, EventArgs e)
        {
            try
            {
                EnableBot();
            }
            catch (ApplicationException err)
            {
                ShowError(err.Message);
                return;
            }
        }

        /// <summary>
        /// показывает MessageBox с заданным текстом и иконкой ошибки
        /// </summary>
        /// <param name="text"></param>
        private void ShowError(string text)
        {
            MessageBox.Show(text, "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        private void EnableBot()
        {
            if (BotEnabled) throw new ApplicationException("Бот уже включён");
            WoWHandle = WoWProcessHandle();
            Log("найден процесс WoW, handle="+WoWHandle);
            //throw new NotImplementedException();
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

        private IntPtr WoWProcessHandle()
        {
            Process[] wows = Process.GetProcessesByName("wow");
            if (wows.Length == 0) throw new ApplicationException("процесс WoW не найден");
            if (wows.Length > 1) throw new ApplicationException("найдено более одного процесса WoW");
            return wows[0].Handle;
        }
    }
}
