using System;
using System.IO;
using System.Windows.Forms;
using FiniteStateMachine;
using Nakamar.Properties;
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
                ManageGroupBox.Text = value ? "Бот включён" : "Бот выключен";
            }
        }
        private WoWMemoryManager.MemoryManager WoW;
        private Engine FSM;
        private ulong PreviousFrameCount;

        private void LogToFileFunction(string text)
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

        private void LogToListBoxFunction(string text)
        {
            LogBox.Items.Add(text);
            if (AutoScrollCheckBox.Checked)
                LogBox.TopIndex = LogBox.Items.Count - 1;
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
            if (Settings.Default.CallUpgrade)
            {
                Logger.RawLog = LogToListBoxFunction;
                UpgradeSettings();
            }

            // а теперь если RawLog Вызовут из другого потока

            Logger.LogFunction tmp = 
                new Logger.LogFunction(LogToFileFunction) + new Logger.LogFunction(LogToListBoxFunction);
            
            Logger.RawLog = delegate(string message)
            {
                if (InvokeRequired)
                    BeginInvoke(tmp, new object[] {message});
                else
                    tmp(message);
            };
            
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
            // Logger-ом пользоваться ещё нельзя
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

            WoW = new WoWMemoryManager.MemoryManager(WoWId);

            FSM = new Engine(WoW);

            // load modules
            Logger.Log("Загружаю состояния из " + Settings.Default.StatesPath);
            FSM.LoadStates(Settings.Default.StatesPath);

            FSM.StartEngine((int)Settings.Default.NeededFPS);
            BotEnabled = true;

            Logger.Log("Бот включён, WoW process id: " + WoWId + ", загружено состояний: " + FSM.States.Count);
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

            // start if needed
            if (!BotEnabled && Settings.Default.AutoEnable && IsOneWoWRunning())
                EnableBot();

            // update fps value
            if (FSM != null)
            {
                CurrentFPSValue.Text = (FSM.FrameCount - PreviousFrameCount).ToString();
                LastStateValue.Text = (FSM.LastState==null) ? "запускается" : FSM.LastState.Name;
                PreviousFrameCount = FSM.FrameCount;
            }
            else
            {
                CurrentFPSValue.Text = "?";
                LastStateValue.Text = "не работает";
                PreviousFrameCount = 0;
            }
        }

        private void SelectLogDirectory(object sender, EventArgs e)
        {
            LogDirectoryBrowser.SelectedPath = Settings.Default.LogDirectory;
            DialogResult result = LogDirectoryBrowser.ShowDialog();
            if (result == DialogResult.OK)
            {
                Settings.Default.LogDirectory = LogDirectoryBrowser.SelectedPath;
                Logger.Log("Директория логов изменена на " + Settings.Default.LogDirectory);
            }
        }

        private void RestartBot(object sender, EventArgs e)
        {
            DisableBot();
            EnableBot();
        }

        private void SelectStatesPath(object sender, EventArgs e)
        {
            StatesPathBrowser.FileName = Settings.Default.StatesPath;
            if (StatesPathBrowser.ShowDialog() == DialogResult.OK)
            {
                Logger.Log("Путь к библиотеке состояний обновлён. Изменения подействуют после перезапуска бота.");
                Settings.Default.StatesPath = StatesPathBrowser.FileName;
            }
        }

    }
}
