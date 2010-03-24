using System;
using System.IO;
using System.Windows.Forms;
using FiniteStateMachine;
using Nakamar.Properties;
using Util;
using System.Diagnostics;
using System.Drawing;
using System.Collections.Generic;
using System.Collections;
using System.Media; // for Logger


namespace Nakamar
{
    public partial class MainForm : Form
    {
        private bool botEnabled;
        private bool BotEnabled
        {
            get { return botEnabled; }
            set
            {
                StatesList.Enabled = StateSettings.Enabled = RestartButton.Enabled = 
                    DisableBotButton.Enabled = botEnabled =
                    BlockedStatesGroup.Enabled = BlockStateButton.Enabled = value;

                EnableBotButton.Enabled = !value;
                Text = value ? "Running" : "Not running";
            }
        }
        private WoWMemoryManager.MemoryManager WoW;
        private Engine FSM;
        private ulong PreviousFrameCount;
        private DateTime lastDisabled = new DateTime(0);
        private LoaderManager LoaderManager = new LoaderManager(Settings.Default.StatesPath);

        static private void Log(string message)
        {
            Logger.Log("Main",  message);
        }

        private void LogToFileFunction(string text)
        {
            if (Settings.Default.SaveLogs)
            {
                if (String.IsNullOrEmpty(Settings.Default.LogDirectory))
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
            if (Settings.Default.AutoScroll)
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
                    BeginInvoke(tmp, new object[] { message });
                else
                    tmp(message);
            };

            Log("Программа запущена");
            
            RestoreWindowState();

            uniqueMonitor(sender, e);
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
            SaveWindowState();
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

            WoW = new WoWMemoryManager.MemoryManager(WoWId);

            FSM = new Engine(WoW);

            // load modules
            Log("Загружаю состояния из " + Settings.Default.StatesPath);
            FSM.LoadStates(Settings.Default.StatesPath);
            FSM.States.Sort();

            UpdateStatesGUI();

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
            if (FSM.DoNotRestart)
            {
                PlayDoNotRestartSound();
                
            }

            WoW = null;
            BotEnabled = false;
            lastDisabled = DateTime.Now;
            Log("Бот остановлен");

            while (FSM.DoNotRestart && IsOneWoWRunning())
            {
                MessageBox.Show(
                    "Произошла ошибка в работе бота, WoW не закрыт. Посмотрите, что c ним произошло, закройте WoW и затем нажмите ОК",
                    "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

            FSM = null;
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

        private bool monitorIsActiveNow = false;
        private object monitorLock = new object();

        private void uniqueMonitor(object sender, EventArgs e)
        {
            lock (monitorLock)
            {
                if (monitorIsActiveNow)
                {
                    return;
                }
                else
                {
                    monitorIsActiveNow = true;
                }
            }

            Monitor(sender, e);

            monitorIsActiveNow = false;
        }

        private void Monitor(object sender, EventArgs e)
        {

            LastStateValue.Text = null;

            // stop bot if something goes wrong
            if (BotEnabled && !(FSM.Running && IsOneWoWRunning()))
            {
                DisableBot();
            }

            // run WoW if needed
            if (Settings.Default.WoWAutoStart && !IsWoWRunning())
            {
                string reason = LoaderManager.WhyShouldntStartWow();

                if (reason == null)
                {
                    StartWoW(sender, e, false);
                }
                else
                {
                    LastStateValue.Text = "Не запускаю WoW: " + reason;
                }
            }
            StartWoWButton.Enabled = !IsWoWRunning();

            // start bot if needed
            if (!BotEnabled && Settings.Default.AutoEnable && IsOneWoWRunning() && (DateTime.Now - lastDisabled).Seconds > 5)
            {
                EnableBot();
            }

            // update fps value
            if (FSM != null)
            {
                CurrentFPSValue.Visible = true;
                lock (FSM.Stats)
                {
                    CurrentFPSValue.Text = "FPS: " + (FSM.FrameCount - PreviousFrameCount);
                    LastStateValue.Text = (FSM.CurrentState == null) ? "запускается" : FSM.CurrentState.Name;
                    PreviousFrameCount = FSM.FrameCount;
                }
            }
            else
            {
                CurrentFPSValue.Visible = false;
                LastStateValue.Text = LastStateValue.Text ?? "не работает";
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
                string name = (string)StatesList.Items[index];
                lock (FSM.Locker)
                {
                    foreach (State state in FSM.States)
                        if (state.GetType().FullName == name)
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
            if (Settings.Default.TransparentLogBox)
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
            StartWoW(sender, e, true);
        }

        private void StartWoW(object sender, EventArgs e, bool needCheck)
        {
            if (File.Exists(Settings.Default.WoWPath))
                if (Settings.Default.WoWPath.EndsWith("Wow.exe"))
                {
                    if(needCheck)
                    {
                        Log("Сейчас проверю");//!!
                        string reason = LoaderManager.WhyShouldntStartWow();
                        if (reason != null)
                        {
                            Log("Не запускаю WoW: " + reason);
                            return;
                        }
                    }
                    LoaderManager.Prepare();
                    Log("Запускаю " + Settings.Default.WoWPath);
                    StartWoWButton.Enabled = false;
                    this.Cursor = Cursors.WaitCursor;
                    this.Refresh();
                    Process.Start(Settings.Default.WoWPath).WaitForInputIdle();
                    Log("WoW запущен");
                    this.Cursor = Cursors.Default;
                }
                else
                    Log("Нужен файл Wow.exe");
            else
                Log("Файл Wow.exe не найден");
        }

        private void BlockStateButton_Click(object sender, EventArgs e)
        {
            int index = StatesList.SelectedIndex;
            if (index == -1)
                ShowError("нужно выбрать состояние из списка прежде чем нажимать кнопку блокирования");
            else
            {
                string name = (string)StatesList.Items[index];
                lock (FSM.Locker)
                {
                    if (FSM.DisabledStates.Contains(name))
                    {
                        ShowError("Это состояние уже заблокировано");
                    }
                    else
                    {
                        FSM.DisabledStates.Add(name);
                        FSM.SaveSettings();
                        UpdateStatesGUI();
                    }
                }
            }
        }

        private void UpdateStatesGUI()
        {
            // update gui list
            StatesList.BeginUpdate();
            StatesList.Items.Clear();

            foreach(State state in FSM.States)
                StatesList.Items.Add(state.GetType().FullName);

            StatesList.EndUpdate();

            BlockedStatesList.BeginUpdate();
            BlockedStatesList.Items.Clear();

            foreach (string blocked in FSM.DisabledStates)
                BlockedStatesList.Items.Add(blocked);

            BlockedStatesList.EndUpdate();
        }

        private void UnBlockButton_Click(object sender, EventArgs e)
        {
            int index = BlockedStatesList.SelectedIndex;
            if (index == -1)
            {
                ShowError("нужно выбрать состояние из списка прежде чем нажимать кнопку разблокирования");
            }
            else
            {
                string name = (string)BlockedStatesList.Items[index];
                lock (FSM.Locker)
                {
                    FSM.DisabledStates.Remove(name);
                    FSM.SaveSettings();
                    UpdateStatesGUI();
                }
            }
        }

        private void SaveWindowState()
        {
            if (WindowState == FormWindowState.Normal)
            {
                Properties.Settings.Default.MainFormLocation = Location;
                Properties.Settings.Default.MainFormSize = Size;
            }
            else
            {
                Properties.Settings.Default.MainFormLocation = RestoreBounds.Location;
                Properties.Settings.Default.MainFormSize = RestoreBounds.Size;
            }
            Properties.Settings.Default.MainFormState = WindowState;
        }

        private void RestoreWindowState()
        {
            if (Properties.Settings.Default.MainFormSize == new Size(0, 0))
            {
                return; // state has never been saved
            }
            StartPosition = FormStartPosition.Manual;
            Location = Properties.Settings.Default.MainFormLocation;
            Size = Properties.Settings.Default.MainFormSize;
            WindowState = Properties.Settings.Default.MainFormState;
        }

        private void PlayDoNotRestartSound()
        {
            SoundPlayer player = new SoundPlayer(Properties.Resources.DoNotRestartSound);
            player.Play();            
        }
    }
}
