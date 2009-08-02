namespace Nakamar
{
    partial class MainForm
    {
        /// <summary>
        /// Требуется переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Обязательный метод для поддержки конструктора - не изменяйте
        /// содержимое данного метода при помощи редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.SaveSettingsTimer = new System.Windows.Forms.Timer(this.components);
            this.Tooltip = new System.Windows.Forms.ToolTip(this.components);
            this.NeededFPSSelector = new System.Windows.Forms.NumericUpDown();
            this.SelectStatesDirectoryButton = new System.Windows.Forms.Button();
            this.StateSettings = new System.Windows.Forms.Button();
            this.AutoEnable = new System.Windows.Forms.CheckBox();
            this.MonitorTimer = new System.Windows.Forms.Timer(this.components);
            this.LogDirectoryBrowser = new System.Windows.Forms.FolderBrowserDialog();
            this.NeededFPSLabel = new System.Windows.Forms.Label();
            this.StatesPathBrowser = new System.Windows.Forms.OpenFileDialog();
            this.StatesSettingsGroup = new System.Windows.Forms.GroupBox();
            this.BlockStateButton = new System.Windows.Forms.Button();
            this.StatesList = new System.Windows.Forms.ListBox();
            this.TopMostCheckBox = new System.Windows.Forms.CheckBox();
            this.OpacityTrackBar = new System.Windows.Forms.TrackBar();
            this.OpacityLabel = new System.Windows.Forms.Label();
            this.Tabs = new System.Windows.Forms.TabControl();
            this.ManagementPage = new System.Windows.Forms.TabPage();
            this.LogBox = new System.Windows.Forms.ListBox();
            this.ManagementPanel = new System.Windows.Forms.Panel();
            this.StartWoWButton = new System.Windows.Forms.Button();
            this.HideManagementButtons = new System.Windows.Forms.CheckBox();
            this.RestartButton = new System.Windows.Forms.Button();
            this.DisableBotButton = new System.Windows.Forms.Button();
            this.EnableBotButton = new System.Windows.Forms.Button();
            this.SettingsPage = new System.Windows.Forms.TabPage();
            this.BlockedStatesGroup = new System.Windows.Forms.GroupBox();
            this.UnBlockButton = new System.Windows.Forms.Button();
            this.BlockedStatesList = new System.Windows.Forms.ListBox();
            this.WoWAutoStart = new System.Windows.Forms.CheckBox();
            this.WoWPath = new System.Windows.Forms.Button();
            this.AutoScrollCheckBox = new System.Windows.Forms.CheckBox();
            this.LogFont = new System.Windows.Forms.Button();
            this.TransparentLogBox = new System.Windows.Forms.CheckBox();
            this.ChangeLogDirectoryButton = new System.Windows.Forms.Button();
            this.LogToFile = new System.Windows.Forms.CheckBox();
            this.StatusBar = new System.Windows.Forms.StatusStrip();
            this.LastStateValue = new System.Windows.Forms.ToolStripStatusLabel();
            this.CurrentFPSValue = new System.Windows.Forms.ToolStripStatusLabel();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.LogBoxFontDialog = new System.Windows.Forms.FontDialog();
            this.WoWPathBrowser = new System.Windows.Forms.OpenFileDialog();
            ((System.ComponentModel.ISupportInitialize)(this.NeededFPSSelector)).BeginInit();
            this.StatesSettingsGroup.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.OpacityTrackBar)).BeginInit();
            this.Tabs.SuspendLayout();
            this.ManagementPage.SuspendLayout();
            this.ManagementPanel.SuspendLayout();
            this.SettingsPage.SuspendLayout();
            this.BlockedStatesGroup.SuspendLayout();
            this.StatusBar.SuspendLayout();
            this.SuspendLayout();
            // 
            // SaveSettingsTimer
            // 
            this.SaveSettingsTimer.Interval = 60000;
            this.SaveSettingsTimer.Tick += new System.EventHandler(this.SaveSettings);
            // 
            // NeededFPSSelector
            // 
            this.NeededFPSSelector.DataBindings.Add(new System.Windows.Forms.Binding("Value", global::Nakamar.Properties.Settings.Default, "NeededFPS", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.NeededFPSSelector.Location = new System.Drawing.Point(99, 92);
            this.NeededFPSSelector.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.NeededFPSSelector.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.NeededFPSSelector.Name = "NeededFPSSelector";
            this.NeededFPSSelector.Size = new System.Drawing.Size(55, 20);
            this.NeededFPSSelector.TabIndex = 8;
            this.Tooltip.SetToolTip(this.NeededFPSSelector, "Изменения подействуют после перезапуска бота");
            this.NeededFPSSelector.Value = global::Nakamar.Properties.Settings.Default.NeededFPS;
            // 
            // SelectStatesDirectoryButton
            // 
            this.SelectStatesDirectoryButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.SelectStatesDirectoryButton.Location = new System.Drawing.Point(6, 84);
            this.SelectStatesDirectoryButton.Name = "SelectStatesDirectoryButton";
            this.SelectStatesDirectoryButton.Size = new System.Drawing.Size(84, 23);
            this.SelectStatesDirectoryButton.TabIndex = 14;
            this.SelectStatesDirectoryButton.Text = "Файл...";
            this.Tooltip.SetToolTip(this.SelectStatesDirectoryButton, "Выбрать директорию с состояниями");
            this.SelectStatesDirectoryButton.UseVisualStyleBackColor = true;
            this.SelectStatesDirectoryButton.Click += new System.EventHandler(this.SelectStatesPath);
            // 
            // StateSettings
            // 
            this.StateSettings.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.StateSettings.Location = new System.Drawing.Point(96, 84);
            this.StateSettings.Name = "StateSettings";
            this.StateSettings.Size = new System.Drawing.Size(84, 23);
            this.StateSettings.TabIndex = 1;
            this.StateSettings.Text = "Настроить...";
            this.Tooltip.SetToolTip(this.StateSettings, "для настройки состояния выберите его из списка выше, когда бот запущен");
            this.StateSettings.UseVisualStyleBackColor = true;
            this.StateSettings.Click += new System.EventHandler(this.ConfigureState);
            // 
            // AutoEnable
            // 
            this.AutoEnable.AutoSize = true;
            this.AutoEnable.Checked = global::Nakamar.Properties.Settings.Default.AutoEnable;
            this.AutoEnable.DataBindings.Add(new System.Windows.Forms.Binding("Checked", global::Nakamar.Properties.Settings.Default, "AutoEnable", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.AutoEnable.Location = new System.Drawing.Point(5, 32);
            this.AutoEnable.Name = "AutoEnable";
            this.AutoEnable.Size = new System.Drawing.Size(85, 17);
            this.AutoEnable.TabIndex = 19;
            this.AutoEnable.Text = "Автозапуск";
            this.Tooltip.SetToolTip(this.AutoEnable, "Автоматически включать бота если обнаружен запущенный WoW");
            this.AutoEnable.UseVisualStyleBackColor = true;
            // 
            // MonitorTimer
            // 
            this.MonitorTimer.Enabled = true;
            this.MonitorTimer.Interval = 1000;
            this.MonitorTimer.Tag = "";
            this.MonitorTimer.Tick += new System.EventHandler(this.Monitor);
            // 
            // LogDirectoryBrowser
            // 
            this.LogDirectoryBrowser.Description = "Выберите директорию для сохранения логов";
            this.LogDirectoryBrowser.SelectedPath = global::Nakamar.Properties.Settings.Default.LogDirectory;
            // 
            // NeededFPSLabel
            // 
            this.NeededFPSLabel.AutoSize = true;
            this.NeededFPSLabel.Location = new System.Drawing.Point(3, 99);
            this.NeededFPSLabel.Name = "NeededFPSLabel";
            this.NeededFPSLabel.Size = new System.Drawing.Size(90, 13);
            this.NeededFPSLabel.TabIndex = 7;
            this.NeededFPSLabel.Text = "Желаемый FPS:";
            // 
            // StatesPathBrowser
            // 
            this.StatesPathBrowser.DefaultExt = "dll";
            this.StatesPathBrowser.FileName = global::Nakamar.Properties.Settings.Default.StatesPath;
            this.StatesPathBrowser.Filter = "Библиотеки (*.dll)|*.dll|Все файлы|*.*";
            this.StatesPathBrowser.Title = "Выбор библиотеки состояний";
            // 
            // StatesSettingsGroup
            // 
            this.StatesSettingsGroup.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)));
            this.StatesSettingsGroup.Controls.Add(this.BlockStateButton);
            this.StatesSettingsGroup.Controls.Add(this.StateSettings);
            this.StatesSettingsGroup.Controls.Add(this.SelectStatesDirectoryButton);
            this.StatesSettingsGroup.Controls.Add(this.StatesList);
            this.StatesSettingsGroup.Location = new System.Drawing.Point(6, 175);
            this.StatesSettingsGroup.Name = "StatesSettingsGroup";
            this.StatesSettingsGroup.Size = new System.Drawing.Size(337, 113);
            this.StatesSettingsGroup.TabIndex = 14;
            this.StatesSettingsGroup.TabStop = false;
            this.StatesSettingsGroup.Text = "Загруженные состояния";
            // 
            // BlockStateButton
            // 
            this.BlockStateButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.BlockStateButton.Location = new System.Drawing.Point(186, 84);
            this.BlockStateButton.Name = "BlockStateButton";
            this.BlockStateButton.Size = new System.Drawing.Size(83, 23);
            this.BlockStateButton.TabIndex = 17;
            this.BlockStateButton.Text = "Блокировать";
            this.BlockStateButton.UseVisualStyleBackColor = true;
            this.BlockStateButton.Click += new System.EventHandler(this.BlockStateButton_Click);
            // 
            // StatesList
            // 
            this.StatesList.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.StatesList.FormattingEnabled = true;
            this.StatesList.IntegralHeight = false;
            this.StatesList.Location = new System.Drawing.Point(6, 19);
            this.StatesList.Name = "StatesList";
            this.StatesList.Size = new System.Drawing.Size(325, 59);
            this.StatesList.Sorted = true;
            this.StatesList.TabIndex = 0;
            this.StatesList.DoubleClick += new System.EventHandler(this.ConfigureState);
            // 
            // TopMostCheckBox
            // 
            this.TopMostCheckBox.AutoSize = true;
            this.TopMostCheckBox.Checked = global::Nakamar.Properties.Settings.Default.TopMost;
            this.TopMostCheckBox.DataBindings.Add(new System.Windows.Forms.Binding("Checked", global::Nakamar.Properties.Settings.Default, "TopMost", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.TopMostCheckBox.Location = new System.Drawing.Point(6, 6);
            this.TopMostCheckBox.Name = "TopMostCheckBox";
            this.TopMostCheckBox.Size = new System.Drawing.Size(116, 17);
            this.TopMostCheckBox.TabIndex = 15;
            this.TopMostCheckBox.Text = "Поверх всех окон";
            this.TopMostCheckBox.UseVisualStyleBackColor = true;
            // 
            // OpacityTrackBar
            // 
            this.OpacityTrackBar.AutoSize = false;
            this.OpacityTrackBar.DataBindings.Add(new System.Windows.Forms.Binding("Value", global::Nakamar.Properties.Settings.Default, "Opacity", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.OpacityTrackBar.LargeChange = 10;
            this.OpacityTrackBar.Location = new System.Drawing.Point(52, 26);
            this.OpacityTrackBar.Maximum = 100;
            this.OpacityTrackBar.Minimum = 1;
            this.OpacityTrackBar.Name = "OpacityTrackBar";
            this.OpacityTrackBar.Size = new System.Drawing.Size(110, 20);
            this.OpacityTrackBar.TabIndex = 16;
            this.OpacityTrackBar.TabStop = false;
            this.OpacityTrackBar.TickStyle = System.Windows.Forms.TickStyle.None;
            this.OpacityTrackBar.Value = global::Nakamar.Properties.Settings.Default.Opacity;
            // 
            // OpacityLabel
            // 
            this.OpacityLabel.AutoSize = true;
            this.OpacityLabel.Location = new System.Drawing.Point(3, 26);
            this.OpacityLabel.Name = "OpacityLabel";
            this.OpacityLabel.Size = new System.Drawing.Size(43, 13);
            this.OpacityLabel.TabIndex = 17;
            this.OpacityLabel.Text = "Альфа:";
            // 
            // Tabs
            // 
            this.Tabs.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.Tabs.Controls.Add(this.ManagementPage);
            this.Tabs.Controls.Add(this.SettingsPage);
            this.Tabs.Location = new System.Drawing.Point(0, 0);
            this.Tabs.Name = "Tabs";
            this.Tabs.SelectedIndex = 0;
            this.Tabs.Size = new System.Drawing.Size(835, 320);
            this.Tabs.TabIndex = 18;
            // 
            // ManagementPage
            // 
            this.ManagementPage.BackColor = System.Drawing.Color.Transparent;
            this.ManagementPage.Controls.Add(this.LogBox);
            this.ManagementPage.Controls.Add(this.ManagementPanel);
            this.ManagementPage.Location = new System.Drawing.Point(4, 22);
            this.ManagementPage.Name = "ManagementPage";
            this.ManagementPage.Padding = new System.Windows.Forms.Padding(3);
            this.ManagementPage.Size = new System.Drawing.Size(827, 294);
            this.ManagementPage.TabIndex = 0;
            this.ManagementPage.Text = "Управление";
            // 
            // LogBox
            // 
            this.LogBox.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(253)))), ((int)(((byte)(254)))));
            this.LogBox.DataBindings.Add(new System.Windows.Forms.Binding("Font", global::Nakamar.Properties.Settings.Default, "LogBoxFont", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.LogBox.DataBindings.Add(new System.Windows.Forms.Binding("ForeColor", global::Nakamar.Properties.Settings.Default, "LogBoxColor", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.LogBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.LogBox.Font = global::Nakamar.Properties.Settings.Default.LogBoxFont;
            this.LogBox.ForeColor = global::Nakamar.Properties.Settings.Default.LogBoxColor;
            this.LogBox.FormattingEnabled = true;
            this.LogBox.IntegralHeight = false;
            this.LogBox.Location = new System.Drawing.Point(3, 55);
            this.LogBox.Name = "LogBox";
            this.LogBox.SelectionMode = System.Windows.Forms.SelectionMode.None;
            this.LogBox.Size = new System.Drawing.Size(821, 236);
            this.LogBox.TabIndex = 7;
            // 
            // ManagementPanel
            // 
            this.ManagementPanel.Controls.Add(this.StartWoWButton);
            this.ManagementPanel.Controls.Add(this.HideManagementButtons);
            this.ManagementPanel.Controls.Add(this.RestartButton);
            this.ManagementPanel.Controls.Add(this.DisableBotButton);
            this.ManagementPanel.Controls.Add(this.EnableBotButton);
            this.ManagementPanel.Controls.Add(this.AutoEnable);
            this.ManagementPanel.Dock = System.Windows.Forms.DockStyle.Top;
            this.ManagementPanel.Location = new System.Drawing.Point(3, 3);
            this.ManagementPanel.Name = "ManagementPanel";
            this.ManagementPanel.Size = new System.Drawing.Size(821, 52);
            this.ManagementPanel.TabIndex = 5;
            // 
            // StartWoWButton
            // 
            this.StartWoWButton.Image = ((System.Drawing.Image)(resources.GetObject("StartWoWButton.Image")));
            this.StartWoWButton.Location = new System.Drawing.Point(197, 3);
            this.StartWoWButton.Name = "StartWoWButton";
            this.StartWoWButton.Size = new System.Drawing.Size(25, 23);
            this.StartWoWButton.TabIndex = 22;
            this.StartWoWButton.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.StartWoWButton.UseVisualStyleBackColor = true;
            this.StartWoWButton.Click += new System.EventHandler(this.StartWoW);
            // 
            // HideManagementButtons
            // 
            this.HideManagementButtons.AutoSize = true;
            this.HideManagementButtons.Checked = global::Nakamar.Properties.Settings.Default.HideButtons;
            this.HideManagementButtons.DataBindings.Add(new System.Windows.Forms.Binding("Checked", global::Nakamar.Properties.Settings.Default, "HideButtons", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.HideManagementButtons.Location = new System.Drawing.Point(96, 32);
            this.HideManagementButtons.Name = "HideManagementButtons";
            this.HideManagementButtons.Size = new System.Drawing.Size(115, 17);
            this.HideManagementButtons.TabIndex = 21;
            this.HideManagementButtons.Text = "Скрывать кнопки";
            this.HideManagementButtons.UseVisualStyleBackColor = true;
            // 
            // RestartButton
            // 
            this.RestartButton.Location = new System.Drawing.Point(133, 3);
            this.RestartButton.Name = "RestartButton";
            this.RestartButton.Size = new System.Drawing.Size(58, 23);
            this.RestartButton.TabIndex = 20;
            this.RestartButton.Text = "Рестарт";
            this.RestartButton.UseVisualStyleBackColor = true;
            this.RestartButton.Click += new System.EventHandler(this.RestartBot);
            // 
            // DisableBotButton
            // 
            this.DisableBotButton.Location = new System.Drawing.Point(69, 3);
            this.DisableBotButton.Name = "DisableBotButton";
            this.DisableBotButton.Size = new System.Drawing.Size(58, 23);
            this.DisableBotButton.TabIndex = 18;
            this.DisableBotButton.Text = "Стоп";
            this.DisableBotButton.UseVisualStyleBackColor = true;
            this.DisableBotButton.Click += new System.EventHandler(this.DisableBot);
            // 
            // EnableBotButton
            // 
            this.EnableBotButton.Location = new System.Drawing.Point(5, 3);
            this.EnableBotButton.Name = "EnableBotButton";
            this.EnableBotButton.Size = new System.Drawing.Size(58, 23);
            this.EnableBotButton.TabIndex = 17;
            this.EnableBotButton.Text = "Старт";
            this.EnableBotButton.UseVisualStyleBackColor = true;
            this.EnableBotButton.Click += new System.EventHandler(this.EnableBotByUser);
            // 
            // SettingsPage
            // 
            this.SettingsPage.Controls.Add(this.BlockedStatesGroup);
            this.SettingsPage.Controls.Add(this.WoWAutoStart);
            this.SettingsPage.Controls.Add(this.WoWPath);
            this.SettingsPage.Controls.Add(this.AutoScrollCheckBox);
            this.SettingsPage.Controls.Add(this.LogFont);
            this.SettingsPage.Controls.Add(this.TransparentLogBox);
            this.SettingsPage.Controls.Add(this.ChangeLogDirectoryButton);
            this.SettingsPage.Controls.Add(this.LogToFile);
            this.SettingsPage.Controls.Add(this.StatesSettingsGroup);
            this.SettingsPage.Controls.Add(this.NeededFPSSelector);
            this.SettingsPage.Controls.Add(this.TopMostCheckBox);
            this.SettingsPage.Controls.Add(this.NeededFPSLabel);
            this.SettingsPage.Controls.Add(this.OpacityLabel);
            this.SettingsPage.Controls.Add(this.OpacityTrackBar);
            this.SettingsPage.Location = new System.Drawing.Point(4, 22);
            this.SettingsPage.Name = "SettingsPage";
            this.SettingsPage.Padding = new System.Windows.Forms.Padding(3);
            this.SettingsPage.Size = new System.Drawing.Size(827, 294);
            this.SettingsPage.TabIndex = 1;
            this.SettingsPage.Text = "Настройки";
            this.SettingsPage.UseVisualStyleBackColor = true;
            // 
            // BlockedStatesGroup
            // 
            this.BlockedStatesGroup.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.BlockedStatesGroup.Controls.Add(this.UnBlockButton);
            this.BlockedStatesGroup.Controls.Add(this.BlockedStatesList);
            this.BlockedStatesGroup.Location = new System.Drawing.Point(439, 175);
            this.BlockedStatesGroup.Name = "BlockedStatesGroup";
            this.BlockedStatesGroup.Size = new System.Drawing.Size(380, 113);
            this.BlockedStatesGroup.TabIndex = 25;
            this.BlockedStatesGroup.TabStop = false;
            this.BlockedStatesGroup.Text = "Заблокированные состояния";
            // 
            // UnBlockButton
            // 
            this.UnBlockButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.UnBlockButton.Location = new System.Drawing.Point(6, 84);
            this.UnBlockButton.Name = "UnBlockButton";
            this.UnBlockButton.Size = new System.Drawing.Size(102, 23);
            this.UnBlockButton.TabIndex = 16;
            this.UnBlockButton.Text = "Разблокировать";
            this.UnBlockButton.UseVisualStyleBackColor = true;
            this.UnBlockButton.Click += new System.EventHandler(this.UnBlockButton_Click);
            // 
            // BlockedStatesList
            // 
            this.BlockedStatesList.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.BlockedStatesList.FormattingEnabled = true;
            this.BlockedStatesList.IntegralHeight = false;
            this.BlockedStatesList.Location = new System.Drawing.Point(6, 19);
            this.BlockedStatesList.Name = "BlockedStatesList";
            this.BlockedStatesList.Size = new System.Drawing.Size(368, 59);
            this.BlockedStatesList.TabIndex = 15;
            // 
            // WoWAutoStart
            // 
            this.WoWAutoStart.AutoSize = true;
            this.WoWAutoStart.Checked = global::Nakamar.Properties.Settings.Default.WoWAutoStart;
            this.WoWAutoStart.DataBindings.Add(new System.Windows.Forms.Binding("Checked", global::Nakamar.Properties.Settings.Default, "WoWAutoStart", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.WoWAutoStart.Location = new System.Drawing.Point(32, 149);
            this.WoWAutoStart.Name = "WoWAutoStart";
            this.WoWAutoStart.Size = new System.Drawing.Size(116, 17);
            this.WoWAutoStart.TabIndex = 24;
            this.WoWAutoStart.Text = "Автозапуск WoW";
            this.WoWAutoStart.UseVisualStyleBackColor = true;
            // 
            // WoWPath
            // 
            this.WoWPath.Location = new System.Drawing.Point(6, 149);
            this.WoWPath.Name = "WoWPath";
            this.WoWPath.Size = new System.Drawing.Size(20, 20);
            this.WoWPath.TabIndex = 23;
            this.WoWPath.Text = "…";
            this.WoWPath.UseVisualStyleBackColor = true;
            this.WoWPath.Click += new System.EventHandler(this.WoWPath_Click);
            // 
            // AutoScrollCheckBox
            // 
            this.AutoScrollCheckBox.AutoSize = true;
            this.AutoScrollCheckBox.Checked = global::Nakamar.Properties.Settings.Default.AutoScroll;
            this.AutoScrollCheckBox.CheckState = System.Windows.Forms.CheckState.Checked;
            this.AutoScrollCheckBox.DataBindings.Add(new System.Windows.Forms.Binding("Checked", global::Nakamar.Properties.Settings.Default, "AutoScroll", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.AutoScrollCheckBox.Location = new System.Drawing.Point(87, 69);
            this.AutoScrollCheckBox.Name = "AutoScrollCheckBox";
            this.AutoScrollCheckBox.Size = new System.Drawing.Size(102, 17);
            this.AutoScrollCheckBox.TabIndex = 22;
            this.AutoScrollCheckBox.Text = "Автопрокрутка";
            this.AutoScrollCheckBox.UseVisualStyleBackColor = true;
            // 
            // LogFont
            // 
            this.LogFont.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F);
            this.LogFont.ForeColor = System.Drawing.SystemColors.WindowText;
            this.LogFont.Location = new System.Drawing.Point(6, 65);
            this.LogFont.Name = "LogFont";
            this.LogFont.Size = new System.Drawing.Size(75, 23);
            this.LogFont.TabIndex = 21;
            this.LogFont.Text = "Шрифт лога";
            this.LogFont.UseVisualStyleBackColor = true;
            this.LogFont.Click += new System.EventHandler(this.LogFont_Click);
            // 
            // TransparentLogBox
            // 
            this.TransparentLogBox.AutoSize = true;
            this.TransparentLogBox.Checked = global::Nakamar.Properties.Settings.Default.TransparentLogBox;
            this.TransparentLogBox.DataBindings.Add(new System.Windows.Forms.Binding("Checked", global::Nakamar.Properties.Settings.Default, "TransparentLogBox", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.TransparentLogBox.Location = new System.Drawing.Point(6, 42);
            this.TransparentLogBox.Name = "TransparentLogBox";
            this.TransparentLogBox.Size = new System.Drawing.Size(102, 17);
            this.TransparentLogBox.TabIndex = 20;
            this.TransparentLogBox.Text = "\"дырявый\" лог";
            this.TransparentLogBox.UseVisualStyleBackColor = true;
            // 
            // ChangeLogDirectoryButton
            // 
            this.ChangeLogDirectoryButton.DataBindings.Add(new System.Windows.Forms.Binding("Enabled", global::Nakamar.Properties.Settings.Default, "SaveLogs", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.ChangeLogDirectoryButton.Enabled = global::Nakamar.Properties.Settings.Default.SaveLogs;
            this.ChangeLogDirectoryButton.Location = new System.Drawing.Point(6, 123);
            this.ChangeLogDirectoryButton.Name = "ChangeLogDirectoryButton";
            this.ChangeLogDirectoryButton.Size = new System.Drawing.Size(20, 20);
            this.ChangeLogDirectoryButton.TabIndex = 19;
            this.ChangeLogDirectoryButton.Text = "…";
            this.ChangeLogDirectoryButton.UseVisualStyleBackColor = true;
            this.ChangeLogDirectoryButton.Click += new System.EventHandler(this.SelectLogDirectory);
            // 
            // LogToFile
            // 
            this.LogToFile.AutoSize = true;
            this.LogToFile.Checked = global::Nakamar.Properties.Settings.Default.SaveLogs;
            this.LogToFile.DataBindings.Add(new System.Windows.Forms.Binding("Checked", global::Nakamar.Properties.Settings.Default, "SaveLogs", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.LogToFile.Location = new System.Drawing.Point(32, 126);
            this.LogToFile.Name = "LogToFile";
            this.LogToFile.Size = new System.Drawing.Size(105, 17);
            this.LogToFile.TabIndex = 18;
            this.LogToFile.Text = "Сохранять логи";
            this.LogToFile.UseVisualStyleBackColor = true;
            // 
            // StatusBar
            // 
            this.StatusBar.GripMargin = new System.Windows.Forms.Padding(0);
            this.StatusBar.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.LastStateValue,
            this.CurrentFPSValue});
            this.StatusBar.Location = new System.Drawing.Point(0, 323);
            this.StatusBar.Name = "StatusBar";
            this.StatusBar.ShowItemToolTips = true;
            this.StatusBar.Size = new System.Drawing.Size(835, 22);
            this.StatusBar.TabIndex = 23;
            // 
            // LastStateValue
            // 
            this.LastStateValue.Name = "LastStateValue";
            this.LastStateValue.Size = new System.Drawing.Size(795, 17);
            this.LastStateValue.Spring = true;
            this.LastStateValue.Text = "state";
            this.LastStateValue.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // CurrentFPSValue
            // 
            this.CurrentFPSValue.Name = "CurrentFPSValue";
            this.CurrentFPSValue.Size = new System.Drawing.Size(25, 17);
            this.CurrentFPSValue.Text = "FPS";
            this.CurrentFPSValue.ToolTipText = "Текущий FPS";
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 2;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(200, 100);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // LogBoxFontDialog
            // 
            this.LogBoxFontDialog.Color = global::Nakamar.Properties.Settings.Default.LogBoxColor;
            this.LogBoxFontDialog.Font = global::Nakamar.Properties.Settings.Default.LogBoxFont;
            this.LogBoxFontDialog.FontMustExist = true;
            this.LogBoxFontDialog.ShowColor = true;
            // 
            // WoWPathBrowser
            // 
            this.WoWPathBrowser.DefaultExt = "exe";
            this.WoWPathBrowser.FileName = "Wow.exe";
            this.WoWPathBrowser.Filter = "Программы (*.exe)|*.exe";
            this.WoWPathBrowser.ReadOnlyChecked = true;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(835, 345);
            this.Controls.Add(this.StatusBar);
            this.Controls.Add(this.Tabs);
            this.DataBindings.Add(new System.Windows.Forms.Binding("Location", global::Nakamar.Properties.Settings.Default, "MainWindowLocation", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.DataBindings.Add(new System.Windows.Forms.Binding("TopMost", global::Nakamar.Properties.Settings.Default, "TopMost", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.Location = global::Nakamar.Properties.Settings.Default.MainWindowLocation;
            this.Name = "MainForm";
            this.Text = "Программа =)";
            this.TopMost = global::Nakamar.Properties.Settings.Default.TopMost;
            this.TransparencyKey = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(253)))), ((int)(((byte)(254)))));
            this.Deactivate += new System.EventHandler(this.OnDeactivated);
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.Activated += new System.EventHandler(this.OnActivated);
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainForm_FormClosing);
            ((System.ComponentModel.ISupportInitialize)(this.NeededFPSSelector)).EndInit();
            this.StatesSettingsGroup.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.OpacityTrackBar)).EndInit();
            this.Tabs.ResumeLayout(false);
            this.ManagementPage.ResumeLayout(false);
            this.ManagementPanel.ResumeLayout(false);
            this.ManagementPanel.PerformLayout();
            this.SettingsPage.ResumeLayout(false);
            this.SettingsPage.PerformLayout();
            this.BlockedStatesGroup.ResumeLayout(false);
            this.StatusBar.ResumeLayout(false);
            this.StatusBar.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Timer SaveSettingsTimer;
        private System.Windows.Forms.ToolTip Tooltip;
        private System.Windows.Forms.Timer MonitorTimer;
        private System.Windows.Forms.FolderBrowserDialog LogDirectoryBrowser;
        private System.Windows.Forms.Label NeededFPSLabel;
        private System.Windows.Forms.NumericUpDown NeededFPSSelector;
        private System.Windows.Forms.Button SelectStatesDirectoryButton;
        private System.Windows.Forms.OpenFileDialog StatesPathBrowser;
        private System.Windows.Forms.GroupBox StatesSettingsGroup;
        private System.Windows.Forms.Button StateSettings;
        private System.Windows.Forms.ListBox StatesList;
        private System.Windows.Forms.CheckBox TopMostCheckBox;
        private System.Windows.Forms.TrackBar OpacityTrackBar;
        private System.Windows.Forms.Label OpacityLabel;
        private System.Windows.Forms.TabControl Tabs;
        private System.Windows.Forms.TabPage ManagementPage;
        private System.Windows.Forms.TabPage SettingsPage;
        private System.Windows.Forms.Button ChangeLogDirectoryButton;
        private System.Windows.Forms.CheckBox LogToFile;
        private System.Windows.Forms.StatusStrip StatusBar;
        private System.Windows.Forms.ToolStripStatusLabel CurrentFPSValue;
        private System.Windows.Forms.ToolStripStatusLabel LastStateValue;
        private System.Windows.Forms.CheckBox TransparentLogBox;
        private System.Windows.Forms.Button LogFont;
        private System.Windows.Forms.CheckBox AutoScrollCheckBox;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.FontDialog LogBoxFontDialog;
        private System.Windows.Forms.Panel ManagementPanel;
        private System.Windows.Forms.CheckBox HideManagementButtons;
        private System.Windows.Forms.Button RestartButton;
        private System.Windows.Forms.Button DisableBotButton;
        private System.Windows.Forms.Button EnableBotButton;
        private System.Windows.Forms.CheckBox AutoEnable;
        private System.Windows.Forms.ListBox LogBox;
        private System.Windows.Forms.Button WoWPath;
        private System.Windows.Forms.CheckBox WoWAutoStart;
        private System.Windows.Forms.OpenFileDialog WoWPathBrowser;
        private System.Windows.Forms.Button StartWoWButton;
        private System.Windows.Forms.ListBox BlockedStatesList;
        private System.Windows.Forms.GroupBox BlockedStatesGroup;
        private System.Windows.Forms.Button BlockStateButton;
        private System.Windows.Forms.Button UnBlockButton;
    }
}

