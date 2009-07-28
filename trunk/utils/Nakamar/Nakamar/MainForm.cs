using System;
using System.IO;
using System.Windows.Forms;
using FiniteStateMachine;
using Nakamar.Properties;
using Util;
using System.Diagnostics;
using System.Drawing;
using System.Collections.Generic; // for Logger


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
                StatesList.Enabled = StateSettings.Enabled = RestartButton.Enabled = 
                    DisableBotButton.Enabled = _botenabled = value;

                EnableBotButton.Enabled = !value;
                Text = value ? "Running" : "Not running";
            }
        }
        private WoWMemoryManager.MemoryManager WoW;
        private Engine FSM;
        private ulong PreviousFrameCount;
        private DateTime lastDisabled = new DateTime(0);
        private DateTime lastStartedWoW = new DateTime(0);

        private void Log(string message)
        {
            Logger.Log("Main",  message);
        }

        private void LogToFileFunction(string text)
        {
            if (Settings.Default.SaveLogs)
            {
                if (Settings.Default.LogDirectory == "")
                {
                    Settings.Default.SaveLogs = false;
                    Logger.LogError("Main", "Не выбрана директория для логов");
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
                BeginInvoke(tmp, new object[] {message});
            };

            Log("Программа запущена");
            Monitor(sender, e);
            
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            DisableBot();
            Log("Программа завершает свою работу");
            SaveSettings();
            Log("Настройки сохранены");
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
            Log("Настройки программы перенесены из предыдущей версии.");
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
            
            Logger.ClearValues();

            if (!IsOneWoWRunning())
                throw new ApplicationException("Должен быть запущен один процесс World of Warcraft");

            int WoWId = WoWProcesses()[0];

            WoW = new WoWMemoryManager.MemoryManager(WoWId,
                Settings.Default.FindPatternCache.Clone() as System.Collections.Hashtable);

            FSM = new Engine(WoW);

            // load modules
            Log("Загружаю состояния из " + Settings.Default.StatesPath);
            FSM.LoadStates(Settings.Default.StatesPath);
            FSM.States.Sort();

            // update gui list
            StatesList.Items.Clear();
            foreach(State state in FSM.States)
                StatesList.Items.Add(state.GetType().FullName);

            FSM.StartEngine((int)Settings.Default.NeededFPS);
            BotEnabled = true;

            Log("Бот включён, WoW process id: " + WoWId + ", загружено состояний: " + FSM.States.Count);
        }

        private void DisableBot(object sender, EventArgs e)
        {
            DisableBot();
        }

        private void DisableBot()
        {
            if (!BotEnabled) return;

            FSM.StopEngine();
            if (FSM.DoNotRestart && (Settings.Default.AutoEnable || Settings.Default.WoWAutoStart))
            {
                Log("Автозапуск WoW и бота отключён");
                Settings.Default.AutoEnable = false;
                Settings.Default.WoWAutoStart = false;
            }
            FSM = null;
            Settings.Default.FindPatternCache = WoW.Cache;
            WoW = null;
            BotEnabled = false;
            lastDisabled = DateTime.Now;
            Log("Бот остановлен");

        }

        private List<int> WoWProcesses()
        {
            List<int> ans = new List<int>();
            foreach (Process p in Process.GetProcessesByName("wow"))
                if (p.MainWindowTitle == "World of Warcraft")
                    ans.Add(p.Id);

            return ans;
        }

        private bool IsOneWoWRunning()
        {
            return WoWProcesses().Count == 1;
        }

        private void Monitor(object sender, EventArgs e)
        {
            // run WoW if needed
            if (Settings.Default.WoWAutoStart && !IsWoWRunning())
                StartWoW(sender, e);

            StartWoWButton.Enabled = !IsWoWRunning();

            // stop bot if something goes wrong
            if (BotEnabled && !(FSM.Running && IsOneWoWRunning()))
                DisableBot();

            // start if needed
            if (!BotEnabled && Settings.Default.AutoEnable && IsOneWoWRunning() && (DateTime.Now-lastDisabled).Ticks>100000000)
                EnableBot();

            // update fps value
            if (FSM != null)
            {
                CurrentFPSValue.Visible = true;
                CurrentFPSValue.Text = "FPS: "+(FSM.FrameCount - PreviousFrameCount);
                LastStateValue.ToolTipText = FSM.CurrentState==null ? "" :
                    FSM.CurrentState.Module + Environment.NewLine + FSM.CurrentState.AssemblyQualifiedName;
                LastStateValue.Text = (FSM.CurrentState==null) ? "запускается" : FSM.CurrentState.Name;
                PreviousFrameCount = FSM.FrameCount;
            }
            else
            {
                CurrentFPSValue.Visible = false;
                LastStateValue.Text = "не работает";
                LastStateValue.ToolTipText = "конечный автомат сейчас не запущен";
                PreviousFrameCount = 0;
            }
        }

        private bool IsWoWRunning()
        {
            return WoWProcesses().Count != 0;
        }

        private void SelectLogDirectory(object sender, EventArgs e)
        {
            LogDirectoryBrowser.SelectedPath = Settings.Default.LogDirectory;
            DialogResult result = LogDirectoryBrowser.ShowDialog();
            if (result == DialogResult.OK)
            {
                Settings.Default.LogDirectory = LogDirectoryBrowser.SelectedPath;
                Log("Директория логов изменена на " + Settings.Default.LogDirectory);
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
                Log("Путь к библиотеке состояний обновлён. Изменения подействуют после перезапуска бота.");
                Settings.Default.StatesPath = StatesPathBrowser.FileName;
            }
        }

        private void ConfigureState(object sender, EventArgs e)
        {
            int index = StatesList.SelectedIndex;
            if (index == -1)
                ShowError("нужно выбрать состояние из списка прежде чем нажимать кнопку настройки");
            else
            {
                string name = StatesList.Items[index] as string;
                foreach(State state in FSM.States)
                    if (state.GetType().FullName == name)
                    {
                        lock (state)
                        {
                            TopMost = false; // чтобы окно конфигурации не было ниже главного
                            state.Configure();
                            TopMost = true;
                        }
                    }
            }
        }

        private void OnDeactivated(object sender, EventArgs e)
        {
            Opacity = (double)Settings.Default.Opacity / 100;
            if (TransparentLogBox.Checked)
                LogBox.BackColor = Color.FromArgb(0xff, 0xfd, 0xfe);
            if(Settings.Default.HideButtons)
            {
                ManagementPanel.Hide();
            }
        }
       
        private void OnActivated(object sender, EventArgs e)
        {
            Opacity = 1;
            LogBox.BackColor = Color.FromName("Window");
            ManagementPanel.Show();
        }

        private void LogFont_Click(object sender, EventArgs e)
        {
            if (LogBoxFontDialog.ShowDialog() == DialogResult.OK)
            {
                Settings.Default.LogBoxFont = LogBoxFontDialog.Font;
                Settings.Default.LogBoxColor = LogBoxFontDialog.Color;
            }
        }

        private void TransparentLogBox_CheckedChanged(object sender, EventArgs e)
        {
            OnActivated(null, null);
        }

        private void WoWPath_Click(object sender, EventArgs e)
        {
            WoWPathBrowser.FileName = Settings.Default.WoWPath;
            if (WoWPathBrowser.ShowDialog() == DialogResult.OK)
                Settings.Default.WoWPath = WoWPathBrowser.FileName;           
        }

        private void StartWoW(object sender, EventArgs e)
        {
            if (File.Exists(Settings.Default.WoWPath))
                if (Settings.Default.WoWPath.EndsWith("Wow.exe"))
                {
                    Log("Запускаю " + Settings.Default.WoWPath);
                    Process.Start(Settings.Default.WoWPath).WaitForInputIdle();
                    Log("WoW запущен");
                }
                else
                    Log("нужен файл Wow.exe");
            else
                Log("Файл Wow.exe не найден");
        }
    }
}
