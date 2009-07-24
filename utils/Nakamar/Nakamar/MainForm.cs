using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Nakamar.Properties;
using FiniteStateMachine;
using Util; // for Logger

namespace Nakamar
{
    public partial class MainForm : Form
    {
        private bool _botenabled;
        private bool BotEnabled
        {
            get { return _botenabled; }
            set
            {
                RestartButton.Enabled = DisableBotButton.Enabled = _botenabled = value;
                EnableBotButton.Enabled = !value;
                BotStateLabel.Text = value ? "Бот включён" : "Бот выключен";
            }
        }
        private WoWMemory.WoWMemory WoW;
        private Engine FSM;
        private ulong PreviousFrameCount;

        void LogToFileFunction(string text)
        {
            if (Settings.Default.SaveLogs)
            {
                if (Settings.Default.LogDirectory == "")
                {
                    Settings.Default.SaveLogs = false;
                    Logger.LogError("Не выбрана директория для логов");
                }
                else
                {
                    System.IO.Directory.CreateDirectory(Settings.Default.LogDirectory);
                    string filename = Settings.Default.LogDirectory + System.IO.Path.DirectorySeparatorChar +
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
            WoWEnabler.Enabled = Settings.Default.AutoEnable; 
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

            if (Settings.Default.CallUpgrade)
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
            Settings.Default.Save();
        }      
        
        private void SaveSettings(object sender, EventArgs e)
        {
            SaveSettings();
        }

        private void UpgradeSettings()
        {
            Settings.Default.Upgrade();
            Settings.Default.CallUpgrade = false;
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

            WoW = new WoWMemory.WoWMemory(WoWId);
            FSM = new Engine(WoW);
            // todo: load modules
            FSM.StartEngine((int)Settings.Default.NeededFPS);
            BotEnabled = true;

            Logger.Log("Бот включён, WoW process id: " + WoWId);
        }

        private void DisableBot(object sender, EventArgs e)
        {
            DisableBot();
        }

        private void DisableBot()
        {
            if (!BotEnabled) return;

            FSM.StopEngine();
            FSM = null;
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

        private void Monitor(object sender, EventArgs e)
        {
            // stop bot if something goes wrong
            if (BotEnabled && !(FSM.Running && IsOneWoWRunning()))
                DisableBot();

            // update fps value
            if (FSM != null)
            {
                CurrentFPSValue.Text = (FSM.FrameCount - PreviousFrameCount).ToString();
                PreviousFrameCount = FSM.FrameCount;
            }
            else
            {
                CurrentFPSValue.Text = "?";
                PreviousFrameCount = 0;
            }
        }

        private void EnableBotIfNeeded(object sender, EventArgs e)
        {
            if (!BotEnabled && IsOneWoWRunning())
                EnableBot();
        }

        private void SelectLogDirectory(object sender, EventArgs e)
        {
            DialogResult result = LogDirectoryBrowser.ShowDialog();
            if (result == DialogResult.OK)
            {
                Settings.Default.LogDirectory = LogDirectoryBrowser.SelectedPath;
                Logger.Log("Директория логов изменена на " + Settings.Default.LogDirectory);
            }
        }

        private void AutoEnable_CheckedChanged(object sender, EventArgs e)
        {
            WoWEnabler.Enabled = (sender as CheckBox).Checked; 
        }

        private void RestartBot(object sender, EventArgs e)
        {
            DisableBot();
            EnableBot();
        }

    }
}
