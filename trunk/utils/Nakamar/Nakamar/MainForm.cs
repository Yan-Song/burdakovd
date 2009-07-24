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
        private bool BotEnabled
        {
            get { return Work.Enabled; }
            set
            {
                DisableBotButton.Enabled = Work.Enabled = value;
                EnableBotButton.Enabled = !value;
                BotStateLabel.Text = value ? "Бот включён" : "Бот выключен";
            }
        }
        private WoWMemory WoW;
        uint Works = 0;

        void LogToFileFunction(string text)
        {
            if (Properties.Settings.Default.SaveLogs)
            {
                if (Properties.Settings.Default.LogDirectory == "")
                {
                    Properties.Settings.Default.SaveLogs = false;
                    Logger.LogError("Не выбрана директория для логов");
                }
                else
                {
                    System.IO.Directory.CreateDirectory(Properties.Settings.Default.LogDirectory);
                    string filename = Properties.Settings.Default.LogDirectory + System.IO.Path.DirectorySeparatorChar +
                        DateTime.Now.ToShortDateString() + ".log";
                    System.IO.StreamWriter writer = new System.IO.StreamWriter(filename, true);
                    writer.WriteLine("[PID: " + System.Diagnostics.Process.GetCurrentProcess().Id + "] " + text);
                    writer.Close();
                }
            }
        }

        /// <summary>
        /// инициализация гуя
        /// </summary>
        public MainForm()
        {
            InitializeComponent();
            BotEnabled = false;
        }

        /// <summary>
        /// некоторая инициализация
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MainForm_Load(object sender, EventArgs e)
        {
            Logger.RawLog = delegate(string text)
            {
                LogBox.Items.Add(text);
                if (AutoScrollCheckBox.Checked)
                    LogBox.TopIndex = LogBox.Items.Count - 1;
            };

            if (Properties.Settings.Default.CallUpgrade)
                UpgradeSettings();

            Logger.RawLog += LogToFileFunction;
            
            Logger.Log("Программа запущена");
            
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            DisableBot();
            Logger.Log("Программа завершает свою работу");
            SaveSettings();
        }

        private void SaveSettings()
        {
            Properties.Settings.Default.Save();
        }      
        
        private void SaveSettings(object sender, EventArgs e)
        {
            SaveSettings();
        }

        private void UpgradeSettings()
        {
            Properties.Settings.Default.Upgrade();
            Properties.Settings.Default.CallUpgrade = false;
            SaveSettings(); 
            Logger.Log("Настройки программы перенесены из предыдущей версии.");
        }

        /// <summary>
        /// показывает MessageBox с заданным текстом и иконкой ошибки
        /// </summary>
        /// <param name="text"></param>
        private void ShowError(string text)
        {
            MessageBox.Show(text, "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
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

        private void EnableBot()
        {
            if (BotEnabled) return;

            if (!IsOneWoWRunning())
                throw new ApplicationException("Должен быть запущен один процесс World of Warcraft");

            int WoWId = WoWProcesses()[0];

            WoW = new WoWMemory(WoWId);                
            BotEnabled = true;

            Logger.Log("Бот включён, WoW process id: " + WoWId);
        }

        private uint FindPattern(Pattern pattern)
        {
            uint ans = WoW.FindPattern(pattern.PatternString, pattern.Mask);
            if (ans == (uint)WoW.MainModule.BaseAddress) throw new ApplicationException("Pattern not found");
            return ans + pattern.Offset;
        }

        private void DisableBot(object sender, EventArgs e)
        {
            DisableBot();
        }

        private void DisableBot()
        {
            if (!BotEnabled) return;

            WoW = null;
            BotEnabled = false;

            Logger.Log("Бот остановлен");

        }

        private void ClearLog(object sender, EventArgs e)
        {
            LogBox.Items.Clear();
        }

        private int[] WoWProcesses()
        {
            return Magic.SProcess.GetProcessesFromWindowTitle("World of Warcraft");
        }

        private bool IsOneWoWRunning()
        {
            int[] ps = WoWProcesses();
            return ps!=null && ps.Length == 1;
        }

        private void DoWork(object sender, EventArgs e)
        {
            DoWork();
        }

        private void DoWork()
        {
            ++Works;
            if (!IsOneWoWRunning())
                DisableBot();
            // здесь смотреть состояние WoW (запускается, экран входа, выбор персонажа, загрузка мира, мир)   
            // и делать сооств. действия
        }

        private void WPSTick(object sender, EventArgs e)
        {
            WPSLabel.Text = "WPS: " + Works;
            Works = 0;
        }

        private void CheckWoW(object sender, EventArgs e)
        {
            if (!BotEnabled && IsOneWoWRunning())
                EnableBot();
        }

        private void SelectLogDirectory(object sender, EventArgs e)
        {
            DialogResult result = LogDirectoryBrowser.ShowDialog();
            if (result == DialogResult.OK)
            {
                Properties.Settings.Default.LogDirectory = LogDirectoryBrowser.SelectedPath;
                Logger.Log("Директория логов изменена на " + Properties.Settings.Default.LogDirectory);
            }
        }

        private void AutoEnable_CheckedChanged(object sender, EventArgs e)
        {
            WoWChecker.Enabled = (sender as CheckBox).Checked; 
        }

    }
}
