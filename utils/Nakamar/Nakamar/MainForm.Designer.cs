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
            this.SaveSettingsTimer = new System.Windows.Forms.Timer(this.components);
            this.LogGroupBox = new System.Windows.Forms.GroupBox();
            this.AutoScrollCheckBox = new System.Windows.Forms.CheckBox();
            this.LogBox = new System.Windows.Forms.ListBox();
            this.ClearLogButton = new System.Windows.Forms.Button();
            this.Tooltip = new System.Windows.Forms.ToolTip(this.components);
            this.NeededFPSSelector = new System.Windows.Forms.NumericUpDown();
            this.AutoEnable = new System.Windows.Forms.CheckBox();
            this.SelectStatesDirectoryButton = new System.Windows.Forms.Button();
            this.StateSettings = new System.Windows.Forms.Button();
            this.MonitorTimer = new System.Windows.Forms.Timer(this.components);
            this.LogDirectoryBrowser = new System.Windows.Forms.FolderBrowserDialog();
            this.NeededFPSLabel = new System.Windows.Forms.Label();
            this.RestartButton = new System.Windows.Forms.Button();
            this.DisableBotButton = new System.Windows.Forms.Button();
            this.EnableBotButton = new System.Windows.Forms.Button();
            this.StatesPathBrowser = new System.Windows.Forms.OpenFileDialog();
            this.StatesSettingsGroup = new System.Windows.Forms.GroupBox();
            this.StatesList = new System.Windows.Forms.ListBox();
            this.TopMostCheckBox = new System.Windows.Forms.CheckBox();
            this.OpacityTrackBar = new System.Windows.Forms.TrackBar();
            this.OpacityLabel = new System.Windows.Forms.Label();
            this.Tabs = new System.Windows.Forms.TabControl();
            this.ManagementPage = new System.Windows.Forms.TabPage();
            this.SettingsPage = new System.Windows.Forms.TabPage();
            this.ChangeLogDirectoryButton = new System.Windows.Forms.Button();
            this.LogToFile = new System.Windows.Forms.CheckBox();
            this.StatusBar = new System.Windows.Forms.StatusStrip();
            this.LastStateValue = new System.Windows.Forms.ToolStripStatusLabel();
            this.CurrentFPSValue = new System.Windows.Forms.ToolStripStatusLabel();
            this.LogGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.NeededFPSSelector)).BeginInit();
            this.StatesSettingsGroup.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.OpacityTrackBar)).BeginInit();
            this.Tabs.SuspendLayout();
            this.ManagementPage.SuspendLayout();
            this.SettingsPage.SuspendLayout();
            this.StatusBar.SuspendLayout();
            this.SuspendLayout();
            // 
            // SaveSettingsTimer
            // 
            this.SaveSettingsTimer.Interval = 60000;
            this.SaveSettingsTimer.Tick += new System.EventHandler(this.SaveSettings);
            // 
            // LogGroupBox
            // 
            this.LogGroupBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.LogGroupBox.Controls.Add(this.AutoScrollCheckBox);
            this.LogGroupBox.Controls.Add(this.LogBox);
            this.LogGroupBox.Controls.Add(this.ClearLogButton);
            this.LogGroupBox.Location = new System.Drawing.Point(3, 58);
            this.LogGroupBox.Name = "LogGroupBox";
            this.LogGroupBox.Size = new System.Drawing.Size(372, 337);
            this.LogGroupBox.TabIndex = 4;
            this.LogGroupBox.TabStop = false;
            this.LogGroupBox.Text = "Лог выполнения";
            // 
            // AutoScrollCheckBox
            // 
            this.AutoScrollCheckBox.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.AutoScrollCheckBox.AutoSize = true;
            this.AutoScrollCheckBox.Checked = global::Nakamar.Properties.Settings.Default.AutoScroll;
            this.AutoScrollCheckBox.CheckState = System.Windows.Forms.CheckState.Checked;
            this.AutoScrollCheckBox.DataBindings.Add(new System.Windows.Forms.Binding("Checked", global::Nakamar.Properties.Settings.Default, "AutoScroll", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.AutoScrollCheckBox.Location = new System.Drawing.Point(6, 314);
            this.AutoScrollCheckBox.Name = "AutoScrollCheckBox";
            this.AutoScrollCheckBox.Size = new System.Drawing.Size(102, 17);
            this.AutoScrollCheckBox.TabIndex = 3;
            this.AutoScrollCheckBox.Text = "Автопрокрутка";
            this.AutoScrollCheckBox.UseVisualStyleBackColor = true;
            // 
            // LogBox
            // 
            this.LogBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.LogBox.FormattingEnabled = true;
            this.LogBox.IntegralHeight = false;
            this.LogBox.Location = new System.Drawing.Point(6, 19);
            this.LogBox.Name = "LogBox";
            this.LogBox.SelectionMode = System.Windows.Forms.SelectionMode.None;
            this.LogBox.Size = new System.Drawing.Size(360, 283);
            this.LogBox.TabIndex = 2;
            // 
            // ClearLogButton
            // 
            this.ClearLogButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.ClearLogButton.Location = new System.Drawing.Point(291, 308);
            this.ClearLogButton.Name = "ClearLogButton";
            this.ClearLogButton.Size = new System.Drawing.Size(75, 23);
            this.ClearLogButton.TabIndex = 1;
            this.ClearLogButton.Text = "Очистить";
            this.ClearLogButton.UseVisualStyleBackColor = true;
            this.ClearLogButton.Click += new System.EventHandler(this.ClearLog);
            // 
            // NeededFPSSelector
            // 
            this.NeededFPSSelector.DataBindings.Add(new System.Windows.Forms.Binding("Value", global::Nakamar.Properties.Settings.Default, "NeededFPS", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.NeededFPSSelector.Location = new System.Drawing.Point(105, 57);
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
            // AutoEnable
            // 
            this.AutoEnable.AutoSize = true;
            this.AutoEnable.Checked = global::Nakamar.Properties.Settings.Default.AutoEnable;
            this.AutoEnable.DataBindings.Add(new System.Windows.Forms.Binding("Checked", global::Nakamar.Properties.Settings.Default, "AutoEnable", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.AutoEnable.Location = new System.Drawing.Point(6, 35);
            this.AutoEnable.Name = "AutoEnable";
            this.AutoEnable.Size = new System.Drawing.Size(85, 17);
            this.AutoEnable.TabIndex = 14;
            this.AutoEnable.Text = "Автозапуск";
            this.Tooltip.SetToolTip(this.AutoEnable, "Автоматически включать бота если обнаружен запущенный WoW");
            this.AutoEnable.UseVisualStyleBackColor = true;
            // 
            // SelectStatesDirectoryButton
            // 
            this.SelectStatesDirectoryButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.SelectStatesDirectoryButton.Location = new System.Drawing.Point(6, 257);
            this.SelectStatesDirectoryButton.Name = "SelectStatesDirectoryButton";
            this.SelectStatesDirectoryButton.Size = new System.Drawing.Size(84, 23);
            this.SelectStatesDirectoryButton.TabIndex = 14;
            this.SelectStatesDirectoryButton.Text = "Состояния...";
            this.Tooltip.SetToolTip(this.SelectStatesDirectoryButton, "Выбрать директорию с состояниями");
            this.SelectStatesDirectoryButton.UseVisualStyleBackColor = true;
            this.SelectStatesDirectoryButton.Click += new System.EventHandler(this.SelectStatesPath);
            // 
            // StateSettings
            // 
            this.StateSettings.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.StateSettings.Location = new System.Drawing.Point(96, 256);
            this.StateSettings.Name = "StateSettings";
            this.StateSettings.Size = new System.Drawing.Size(84, 25);
            this.StateSettings.TabIndex = 1;
            this.StateSettings.Text = "Настроить...";
            this.Tooltip.SetToolTip(this.StateSettings, "для настройки состояния выберите его из списка выше, когда бот запущен");
            this.StateSettings.UseVisualStyleBackColor = true;
            this.StateSettings.Click += new System.EventHandler(this.ConfigureState);
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
            this.NeededFPSLabel.Location = new System.Drawing.Point(3, 59);
            this.NeededFPSLabel.Name = "NeededFPSLabel";
            this.NeededFPSLabel.Size = new System.Drawing.Size(90, 13);
            this.NeededFPSLabel.TabIndex = 7;
            this.NeededFPSLabel.Text = "Желаемый FPS:";
            // 
            // RestartButton
            // 
            this.RestartButton.Location = new System.Drawing.Point(134, 6);
            this.RestartButton.Name = "RestartButton";
            this.RestartButton.Size = new System.Drawing.Size(58, 23);
            this.RestartButton.TabIndex = 15;
            this.RestartButton.Text = "Рестарт";
            this.RestartButton.UseVisualStyleBackColor = true;
            this.RestartButton.Click += new System.EventHandler(this.RestartBot);
            // 
            // DisableBotButton
            // 
            this.DisableBotButton.Location = new System.Drawing.Point(70, 6);
            this.DisableBotButton.Name = "DisableBotButton";
            this.DisableBotButton.Size = new System.Drawing.Size(58, 23);
            this.DisableBotButton.TabIndex = 13;
            this.DisableBotButton.Text = "Стоп";
            this.DisableBotButton.UseVisualStyleBackColor = true;
            this.DisableBotButton.Click += new System.EventHandler(this.DisableBot);
            // 
            // EnableBotButton
            // 
            this.EnableBotButton.Location = new System.Drawing.Point(6, 6);
            this.EnableBotButton.Name = "EnableBotButton";
            this.EnableBotButton.Size = new System.Drawing.Size(58, 23);
            this.EnableBotButton.TabIndex = 11;
            this.EnableBotButton.Text = "Старт";
            this.EnableBotButton.UseVisualStyleBackColor = true;
            this.EnableBotButton.Click += new System.EventHandler(this.EnableBotByUser);
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
            this.StatesSettingsGroup.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.StatesSettingsGroup.Controls.Add(this.StateSettings);
            this.StatesSettingsGroup.Controls.Add(this.SelectStatesDirectoryButton);
            this.StatesSettingsGroup.Controls.Add(this.StatesList);
            this.StatesSettingsGroup.Location = new System.Drawing.Point(6, 109);
            this.StatesSettingsGroup.Name = "StatesSettingsGroup";
            this.StatesSettingsGroup.Size = new System.Drawing.Size(369, 286);
            this.StatesSettingsGroup.TabIndex = 14;
            this.StatesSettingsGroup.TabStop = false;
            this.StatesSettingsGroup.Text = "Настройки состояний";
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
            this.StatesList.Size = new System.Drawing.Size(357, 232);
            this.StatesList.Sorted = true;
            this.StatesList.TabIndex = 0;
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
            this.OpacityTrackBar.Location = new System.Drawing.Point(55, 36);
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
            this.OpacityLabel.Location = new System.Drawing.Point(3, 36);
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
            this.Tabs.Size = new System.Drawing.Size(389, 427);
            this.Tabs.TabIndex = 18;
            // 
            // ManagementPage
            // 
            this.ManagementPage.Controls.Add(this.RestartButton);
            this.ManagementPage.Controls.Add(this.DisableBotButton);
            this.ManagementPage.Controls.Add(this.LogGroupBox);
            this.ManagementPage.Controls.Add(this.EnableBotButton);
            this.ManagementPage.Controls.Add(this.AutoEnable);
            this.ManagementPage.Location = new System.Drawing.Point(4, 22);
            this.ManagementPage.Name = "ManagementPage";
            this.ManagementPage.Padding = new System.Windows.Forms.Padding(3);
            this.ManagementPage.Size = new System.Drawing.Size(381, 401);
            this.ManagementPage.TabIndex = 0;
            this.ManagementPage.Text = "Управление";
            this.ManagementPage.UseVisualStyleBackColor = true;
            // 
            // SettingsPage
            // 
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
            this.SettingsPage.Size = new System.Drawing.Size(381, 401);
            this.SettingsPage.TabIndex = 1;
            this.SettingsPage.Text = "Настройки";
            this.SettingsPage.UseVisualStyleBackColor = true;
            // 
            // ChangeLogDirectoryButton
            // 
            this.ChangeLogDirectoryButton.DataBindings.Add(new System.Windows.Forms.Binding("Enabled", global::Nakamar.Properties.Settings.Default, "SaveLogs", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.ChangeLogDirectoryButton.Enabled = global::Nakamar.Properties.Settings.Default.SaveLogs;
            this.ChangeLogDirectoryButton.Location = new System.Drawing.Point(6, 83);
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
            this.LogToFile.Location = new System.Drawing.Point(32, 86);
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
            this.StatusBar.Location = new System.Drawing.Point(0, 430);
            this.StatusBar.Name = "StatusBar";
            this.StatusBar.ShowItemToolTips = true;
            this.StatusBar.Size = new System.Drawing.Size(389, 22);
            this.StatusBar.TabIndex = 23;
            // 
            // LastStateValue
            // 
            this.LastStateValue.Name = "LastStateValue";
            this.LastStateValue.Size = new System.Drawing.Size(349, 17);
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
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(389, 452);
            this.Controls.Add(this.StatusBar);
            this.Controls.Add(this.Tabs);
            this.DataBindings.Add(new System.Windows.Forms.Binding("Location", global::Nakamar.Properties.Settings.Default, "MainWindowLocation", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.DataBindings.Add(new System.Windows.Forms.Binding("TopMost", global::Nakamar.Properties.Settings.Default, "TopMost", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.Location = global::Nakamar.Properties.Settings.Default.MainWindowLocation;
            this.Name = "MainForm";
            this.Text = "Программа =)";
            this.TopMost = global::Nakamar.Properties.Settings.Default.TopMost;
            this.Deactivate += new System.EventHandler(this.DoTransparency);
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.Activated += new System.EventHandler(this.RemoveTransparency);
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainForm_FormClosing);
            this.LogGroupBox.ResumeLayout(false);
            this.LogGroupBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.NeededFPSSelector)).EndInit();
            this.StatesSettingsGroup.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.OpacityTrackBar)).EndInit();
            this.Tabs.ResumeLayout(false);
            this.ManagementPage.ResumeLayout(false);
            this.ManagementPage.PerformLayout();
            this.SettingsPage.ResumeLayout(false);
            this.SettingsPage.PerformLayout();
            this.StatusBar.ResumeLayout(false);
            this.StatusBar.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Timer SaveSettingsTimer;
        private System.Windows.Forms.GroupBox LogGroupBox;
        private System.Windows.Forms.ListBox LogBox;
        private System.Windows.Forms.Button ClearLogButton;
        private System.Windows.Forms.ToolTip Tooltip;
        private System.Windows.Forms.CheckBox AutoScrollCheckBox;
        private System.Windows.Forms.Timer MonitorTimer;
        private System.Windows.Forms.FolderBrowserDialog LogDirectoryBrowser;
        private System.Windows.Forms.Label NeededFPSLabel;
        private System.Windows.Forms.NumericUpDown NeededFPSSelector;
        private System.Windows.Forms.Button RestartButton;
        private System.Windows.Forms.CheckBox AutoEnable;
        private System.Windows.Forms.Button DisableBotButton;
        private System.Windows.Forms.Button EnableBotButton;
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
    }
}

