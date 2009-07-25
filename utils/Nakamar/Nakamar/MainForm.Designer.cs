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
            this.ChangeLogDirectoryButton = new System.Windows.Forms.Button();
            this.LogToFile = new System.Windows.Forms.CheckBox();
            this.AutoScrollCheckBox = new System.Windows.Forms.CheckBox();
            this.LogBox = new System.Windows.Forms.ListBox();
            this.ClearLogButton = new System.Windows.Forms.Button();
            this.Tooltip = new System.Windows.Forms.ToolTip(this.components);
            this.FPSLabel = new System.Windows.Forms.Label();
            this.NeededFPSSelector = new System.Windows.Forms.NumericUpDown();
            this.AutoEnable = new System.Windows.Forms.CheckBox();
            this.SelectStatesDirectoryButton = new System.Windows.Forms.Button();
            this.MonitorTimer = new System.Windows.Forms.Timer(this.components);
            this.LogDirectoryBrowser = new System.Windows.Forms.FolderBrowserDialog();
            this.NeededFPSLabel = new System.Windows.Forms.Label();
            this.CurrentFPSValue = new System.Windows.Forms.Label();
            this.ManageGroupBox = new System.Windows.Forms.GroupBox();
            this.RestartButton = new System.Windows.Forms.Button();
            this.DisableBotButton = new System.Windows.Forms.Button();
            this.EnableBotButton = new System.Windows.Forms.Button();
            this.StatusGroupBox = new System.Windows.Forms.GroupBox();
            this.LastStateValue = new System.Windows.Forms.Label();
            this.StatesPathBrowser = new System.Windows.Forms.OpenFileDialog();
            this.LogGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.NeededFPSSelector)).BeginInit();
            this.ManageGroupBox.SuspendLayout();
            this.StatusGroupBox.SuspendLayout();
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
            this.LogGroupBox.Controls.Add(this.ChangeLogDirectoryButton);
            this.LogGroupBox.Controls.Add(this.LogToFile);
            this.LogGroupBox.Controls.Add(this.AutoScrollCheckBox);
            this.LogGroupBox.Controls.Add(this.LogBox);
            this.LogGroupBox.Controls.Add(this.ClearLogButton);
            this.LogGroupBox.Location = new System.Drawing.Point(12, 151);
            this.LogGroupBox.Name = "LogGroupBox";
            this.LogGroupBox.Size = new System.Drawing.Size(543, 277);
            this.LogGroupBox.TabIndex = 4;
            this.LogGroupBox.TabStop = false;
            this.LogGroupBox.Text = "Лог выполнения";
            // 
            // ChangeLogDirectoryButton
            // 
            this.ChangeLogDirectoryButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.ChangeLogDirectoryButton.DataBindings.Add(new System.Windows.Forms.Binding("Enabled", global::Nakamar.Properties.Settings.Default, "SaveLogs", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.ChangeLogDirectoryButton.Enabled = global::Nakamar.Properties.Settings.Default.SaveLogs;
            this.ChangeLogDirectoryButton.Location = new System.Drawing.Point(165, 225);
            this.ChangeLogDirectoryButton.Name = "ChangeLogDirectoryButton";
            this.ChangeLogDirectoryButton.Size = new System.Drawing.Size(123, 23);
            this.ChangeLogDirectoryButton.TabIndex = 5;
            this.ChangeLogDirectoryButton.Text = "Выбрать директорию";
            this.ChangeLogDirectoryButton.UseVisualStyleBackColor = true;
            this.ChangeLogDirectoryButton.Click += new System.EventHandler(this.SelectLogDirectory);
            // 
            // LogToFile
            // 
            this.LogToFile.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.LogToFile.AutoSize = true;
            this.LogToFile.Checked = global::Nakamar.Properties.Settings.Default.SaveLogs;
            this.LogToFile.DataBindings.Add(new System.Windows.Forms.Binding("Checked", global::Nakamar.Properties.Settings.Default, "SaveLogs", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.LogToFile.Location = new System.Drawing.Point(6, 231);
            this.LogToFile.Name = "LogToFile";
            this.LogToFile.Size = new System.Drawing.Size(153, 17);
            this.LogToFile.TabIndex = 4;
            this.LogToFile.Text = "Сохранять логи на диске";
            this.LogToFile.UseVisualStyleBackColor = true;
            // 
            // AutoScrollCheckBox
            // 
            this.AutoScrollCheckBox.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.AutoScrollCheckBox.AutoSize = true;
            this.AutoScrollCheckBox.Checked = global::Nakamar.Properties.Settings.Default.AutoScroll;
            this.AutoScrollCheckBox.CheckState = System.Windows.Forms.CheckState.Checked;
            this.AutoScrollCheckBox.DataBindings.Add(new System.Windows.Forms.Binding("Checked", global::Nakamar.Properties.Settings.Default, "AutoScroll", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.AutoScrollCheckBox.Location = new System.Drawing.Point(6, 254);
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
            this.LogBox.Size = new System.Drawing.Size(531, 200);
            this.LogBox.TabIndex = 2;
            // 
            // ClearLogButton
            // 
            this.ClearLogButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.ClearLogButton.Location = new System.Drawing.Point(462, 248);
            this.ClearLogButton.Name = "ClearLogButton";
            this.ClearLogButton.Size = new System.Drawing.Size(75, 23);
            this.ClearLogButton.TabIndex = 1;
            this.ClearLogButton.Text = "Очистить";
            this.ClearLogButton.UseVisualStyleBackColor = true;
            this.ClearLogButton.Click += new System.EventHandler(this.ClearLog);
            // 
            // FPSLabel
            // 
            this.FPSLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.FPSLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.FPSLabel.Location = new System.Drawing.Point(6, 42);
            this.FPSLabel.Name = "FPSLabel";
            this.FPSLabel.Size = new System.Drawing.Size(78, 20);
            this.FPSLabel.TabIndex = 5;
            this.FPSLabel.Text = "Текущий FPS:";
            this.FPSLabel.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.Tooltip.SetToolTip(this.FPSLabel, "\"Frames per second\"\r\nСтолько раз в секунду выполняется основной цикл бота.");
            // 
            // NeededFPSSelector
            // 
            this.NeededFPSSelector.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.NeededFPSSelector.DataBindings.Add(new System.Windows.Forms.Binding("Value", global::Nakamar.Properties.Settings.Default, "NeededFPS", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.NeededFPSSelector.Location = new System.Drawing.Point(113, 19);
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
            this.AutoEnable.Location = new System.Drawing.Point(6, 19);
            this.AutoEnable.Name = "AutoEnable";
            this.AutoEnable.Size = new System.Drawing.Size(85, 17);
            this.AutoEnable.TabIndex = 14;
            this.AutoEnable.Text = "Автозапуск";
            this.Tooltip.SetToolTip(this.AutoEnable, "Автоматически включать бота если обнаружен запущенный WoW");
            this.AutoEnable.UseVisualStyleBackColor = true;
            // 
            // SelectStatesDirectoryButton
            // 
            this.SelectStatesDirectoryButton.Location = new System.Drawing.Point(6, 104);
            this.SelectStatesDirectoryButton.Name = "SelectStatesDirectoryButton";
            this.SelectStatesDirectoryButton.Size = new System.Drawing.Size(162, 23);
            this.SelectStatesDirectoryButton.TabIndex = 14;
            this.SelectStatesDirectoryButton.Text = "Состояния...";
            this.Tooltip.SetToolTip(this.SelectStatesDirectoryButton, "Выбрать директорию с состояниями");
            this.SelectStatesDirectoryButton.UseVisualStyleBackColor = true;
            this.SelectStatesDirectoryButton.Click += new System.EventHandler(this.SelectStatesPath);
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
            this.NeededFPSLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.NeededFPSLabel.AutoSize = true;
            this.NeededFPSLabel.Location = new System.Drawing.Point(6, 21);
            this.NeededFPSLabel.Name = "NeededFPSLabel";
            this.NeededFPSLabel.Size = new System.Drawing.Size(90, 13);
            this.NeededFPSLabel.TabIndex = 7;
            this.NeededFPSLabel.Text = "Желаемый FPS:";
            // 
            // CurrentFPSValue
            // 
            this.CurrentFPSValue.Location = new System.Drawing.Point(113, 42);
            this.CurrentFPSValue.Name = "CurrentFPSValue";
            this.CurrentFPSValue.Size = new System.Drawing.Size(37, 20);
            this.CurrentFPSValue.TabIndex = 9;
            this.CurrentFPSValue.Text = "?";
            this.CurrentFPSValue.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // ManageGroupBox
            // 
            this.ManageGroupBox.Controls.Add(this.RestartButton);
            this.ManageGroupBox.Controls.Add(this.DisableBotButton);
            this.ManageGroupBox.Controls.Add(this.EnableBotButton);
            this.ManageGroupBox.Controls.Add(this.AutoEnable);
            this.ManageGroupBox.Location = new System.Drawing.Point(12, 12);
            this.ManageGroupBox.Name = "ManageGroupBox";
            this.ManageGroupBox.Size = new System.Drawing.Size(108, 133);
            this.ManageGroupBox.TabIndex = 12;
            this.ManageGroupBox.TabStop = false;
            this.ManageGroupBox.Text = "Управление";
            // 
            // RestartButton
            // 
            this.RestartButton.Location = new System.Drawing.Point(6, 104);
            this.RestartButton.Name = "RestartButton";
            this.RestartButton.Size = new System.Drawing.Size(95, 23);
            this.RestartButton.TabIndex = 15;
            this.RestartButton.Text = "Перезапустить";
            this.RestartButton.UseVisualStyleBackColor = true;
            this.RestartButton.Click += new System.EventHandler(this.RestartBot);
            // 
            // DisableBotButton
            // 
            this.DisableBotButton.Location = new System.Drawing.Point(7, 75);
            this.DisableBotButton.Name = "DisableBotButton";
            this.DisableBotButton.Size = new System.Drawing.Size(95, 23);
            this.DisableBotButton.TabIndex = 13;
            this.DisableBotButton.Text = "Выключить";
            this.DisableBotButton.UseVisualStyleBackColor = true;
            this.DisableBotButton.Click += new System.EventHandler(this.DisableBot);
            // 
            // EnableBotButton
            // 
            this.EnableBotButton.Location = new System.Drawing.Point(6, 46);
            this.EnableBotButton.Name = "EnableBotButton";
            this.EnableBotButton.Size = new System.Drawing.Size(95, 23);
            this.EnableBotButton.TabIndex = 11;
            this.EnableBotButton.Text = "Включить";
            this.EnableBotButton.UseVisualStyleBackColor = true;
            this.EnableBotButton.Click += new System.EventHandler(this.EnableBotByUser);
            // 
            // StatusGroupBox
            // 
            this.StatusGroupBox.Controls.Add(this.LastStateValue);
            this.StatusGroupBox.Controls.Add(this.SelectStatesDirectoryButton);
            this.StatusGroupBox.Controls.Add(this.NeededFPSSelector);
            this.StatusGroupBox.Controls.Add(this.FPSLabel);
            this.StatusGroupBox.Controls.Add(this.CurrentFPSValue);
            this.StatusGroupBox.Controls.Add(this.NeededFPSLabel);
            this.StatusGroupBox.Location = new System.Drawing.Point(126, 12);
            this.StatusGroupBox.Name = "StatusGroupBox";
            this.StatusGroupBox.Size = new System.Drawing.Size(174, 133);
            this.StatusGroupBox.TabIndex = 13;
            this.StatusGroupBox.TabStop = false;
            this.StatusGroupBox.Text = "Опции";
            // 
            // LastStateValue
            // 
            this.LastStateValue.AutoSize = true;
            this.LastStateValue.Location = new System.Drawing.Point(17, 75);
            this.LastStateValue.Name = "LastStateValue";
            this.LastStateValue.Size = new System.Drawing.Size(0, 13);
            this.LastStateValue.TabIndex = 16;
            // 
            // StatesPathBrowser
            // 
            this.StatesPathBrowser.DefaultExt = "dll";
            this.StatesPathBrowser.FileName = global::Nakamar.Properties.Settings.Default.StatesPath;
            this.StatesPathBrowser.Filter = "Библиотеки (*.dll)|*.dll|Все файлы|*.*";
            this.StatesPathBrowser.Title = "Выбор библиотеки состояний";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(567, 440);
            this.Controls.Add(this.StatusGroupBox);
            this.Controls.Add(this.ManageGroupBox);
            this.Controls.Add(this.LogGroupBox);
            this.DataBindings.Add(new System.Windows.Forms.Binding("Location", global::Nakamar.Properties.Settings.Default, "MainWindowLocation", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.Location = global::Nakamar.Properties.Settings.Default.MainWindowLocation;
            this.Name = "MainForm";
            this.Text = "Программа =)";
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.MainForm_FormClosed);
            this.LogGroupBox.ResumeLayout(false);
            this.LogGroupBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.NeededFPSSelector)).EndInit();
            this.ManageGroupBox.ResumeLayout(false);
            this.ManageGroupBox.PerformLayout();
            this.StatusGroupBox.ResumeLayout(false);
            this.StatusGroupBox.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Timer SaveSettingsTimer;
        private System.Windows.Forms.GroupBox LogGroupBox;
        private System.Windows.Forms.ListBox LogBox;
        private System.Windows.Forms.Button ClearLogButton;
        private System.Windows.Forms.ToolTip Tooltip;
        private System.Windows.Forms.CheckBox AutoScrollCheckBox;
        private System.Windows.Forms.Label FPSLabel;
        private System.Windows.Forms.Timer MonitorTimer;
        private System.Windows.Forms.CheckBox LogToFile;
        private System.Windows.Forms.Button ChangeLogDirectoryButton;
        private System.Windows.Forms.FolderBrowserDialog LogDirectoryBrowser;
        private System.Windows.Forms.Label NeededFPSLabel;
        private System.Windows.Forms.NumericUpDown NeededFPSSelector;
        private System.Windows.Forms.Label CurrentFPSValue;
        private System.Windows.Forms.GroupBox ManageGroupBox;
        private System.Windows.Forms.Button RestartButton;
        private System.Windows.Forms.CheckBox AutoEnable;
        private System.Windows.Forms.Button DisableBotButton;
        private System.Windows.Forms.Button EnableBotButton;
        private System.Windows.Forms.GroupBox StatusGroupBox;
        private System.Windows.Forms.Button SelectStatesDirectoryButton;
        private System.Windows.Forms.OpenFileDialog StatesPathBrowser;
        private System.Windows.Forms.Label LastStateValue;
    }
}

