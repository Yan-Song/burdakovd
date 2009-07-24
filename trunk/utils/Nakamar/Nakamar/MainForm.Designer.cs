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
            this.EnableBotButton = new System.Windows.Forms.Button();
            this.BotStateLabel = new System.Windows.Forms.Label();
            this.DisableBotButton = new System.Windows.Forms.Button();
            this.AutoEnable = new System.Windows.Forms.CheckBox();
            this.LogGroupBox = new System.Windows.Forms.GroupBox();
            this.ChangeLogDirectoryButton = new System.Windows.Forms.Button();
            this.LogToFile = new System.Windows.Forms.CheckBox();
            this.AutoScrollCheckBox = new System.Windows.Forms.CheckBox();
            this.LogBox = new System.Windows.Forms.ListBox();
            this.ClearLogButton = new System.Windows.Forms.Button();
            this.Tooltip = new System.Windows.Forms.ToolTip(this.components);
            this.WPSLabel = new System.Windows.Forms.Label();
            this.Work = new System.Windows.Forms.Timer(this.components);
            this.WPSTimer = new System.Windows.Forms.Timer(this.components);
            this.WoWChecker = new System.Windows.Forms.Timer(this.components);
            this.LogDirectoryBrowser = new System.Windows.Forms.FolderBrowserDialog();
            this.LogGroupBox.SuspendLayout();
            this.SuspendLayout();
            // 
            // SaveSettingsTimer
            // 
            this.SaveSettingsTimer.Interval = 60000;
            this.SaveSettingsTimer.Tick += new System.EventHandler(this.SaveSettings);
            // 
            // EnableBotButton
            // 
            this.EnableBotButton.Location = new System.Drawing.Point(12, 25);
            this.EnableBotButton.Name = "EnableBotButton";
            this.EnableBotButton.Size = new System.Drawing.Size(76, 23);
            this.EnableBotButton.TabIndex = 0;
            this.EnableBotButton.Text = "Включить";
            this.EnableBotButton.UseVisualStyleBackColor = true;
            this.EnableBotButton.Click += new System.EventHandler(this.EnableBotByUser);
            // 
            // BotStateLabel
            // 
            this.BotStateLabel.AutoSize = true;
            this.BotStateLabel.Location = new System.Drawing.Point(12, 9);
            this.BotStateLabel.Name = "BotStateLabel";
            this.BotStateLabel.Size = new System.Drawing.Size(85, 13);
            this.BotStateLabel.TabIndex = 1;
            this.BotStateLabel.Text = "Бот в(ы)ключен";
            // 
            // DisableBotButton
            // 
            this.DisableBotButton.Location = new System.Drawing.Point(94, 25);
            this.DisableBotButton.Name = "DisableBotButton";
            this.DisableBotButton.Size = new System.Drawing.Size(76, 23);
            this.DisableBotButton.TabIndex = 2;
            this.DisableBotButton.Text = "Выключить";
            this.DisableBotButton.UseVisualStyleBackColor = true;
            this.DisableBotButton.Click += new System.EventHandler(this.DisableBot);
            // 
            // AutoEnable
            // 
            this.AutoEnable.AutoSize = true;
            this.AutoEnable.Checked = global::Nakamar.Properties.Settings.Default.AutoEnable;
            this.AutoEnable.DataBindings.Add(new System.Windows.Forms.Binding("Checked", global::Nakamar.Properties.Settings.Default, "AutoEnable", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.AutoEnable.Location = new System.Drawing.Point(12, 55);
            this.AutoEnable.Name = "AutoEnable";
            this.AutoEnable.Size = new System.Drawing.Size(85, 17);
            this.AutoEnable.TabIndex = 3;
            this.AutoEnable.Text = "Автозапуск";
            this.Tooltip.SetToolTip(this.AutoEnable, "Автоматически включать бота если обнаружен запущенный WoW");
            this.AutoEnable.UseVisualStyleBackColor = true;
            this.AutoEnable.CheckedChanged += new System.EventHandler(this.AutoEnable_CheckedChanged);
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
            this.LogGroupBox.Location = new System.Drawing.Point(12, 78);
            this.LogGroupBox.Name = "LogGroupBox";
            this.LogGroupBox.Size = new System.Drawing.Size(543, 254);
            this.LogGroupBox.TabIndex = 4;
            this.LogGroupBox.TabStop = false;
            this.LogGroupBox.Text = "Лог выполнения";
            // 
            // ChangeLogDirectoryButton
            // 
            this.ChangeLogDirectoryButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.ChangeLogDirectoryButton.DataBindings.Add(new System.Windows.Forms.Binding("Enabled", global::Nakamar.Properties.Settings.Default, "SaveLogs", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.ChangeLogDirectoryButton.Enabled = global::Nakamar.Properties.Settings.Default.SaveLogs;
            this.ChangeLogDirectoryButton.Location = new System.Drawing.Point(165, 202);
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
            this.LogToFile.Location = new System.Drawing.Point(6, 208);
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
            this.AutoScrollCheckBox.Location = new System.Drawing.Point(6, 231);
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
            this.LogBox.Size = new System.Drawing.Size(531, 177);
            this.LogBox.TabIndex = 2;
            // 
            // ClearLogButton
            // 
            this.ClearLogButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.ClearLogButton.Location = new System.Drawing.Point(462, 225);
            this.ClearLogButton.Name = "ClearLogButton";
            this.ClearLogButton.Size = new System.Drawing.Size(75, 23);
            this.ClearLogButton.TabIndex = 1;
            this.ClearLogButton.Text = "Очистить";
            this.ClearLogButton.UseVisualStyleBackColor = true;
            this.ClearLogButton.Click += new System.EventHandler(this.ClearLog);
            // 
            // WPSLabel
            // 
            this.WPSLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.WPSLabel.AutoSize = true;
            this.WPSLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.WPSLabel.Location = new System.Drawing.Point(505, 9);
            this.WPSLabel.Name = "WPSLabel";
            this.WPSLabel.Size = new System.Drawing.Size(50, 13);
            this.WPSLabel.TabIndex = 5;
            this.WPSLabel.Text = "WPS: ?";
            this.Tooltip.SetToolTip(this.WPSLabel, "\"Works per second\"\r\nСтолько раз в секунду выполняется основной цикл бота.");
            // 
            // Work
            // 
            this.Work.Interval = 50;
            this.Work.Tick += new System.EventHandler(this.DoWork);
            // 
            // WPSTimer
            // 
            this.WPSTimer.Enabled = true;
            this.WPSTimer.Interval = 1000;
            this.WPSTimer.Tag = "";
            this.WPSTimer.Tick += new System.EventHandler(this.WPSTick);
            // 
            // WoWChecker
            // 
            this.WoWChecker.Interval = 1000;
            this.WoWChecker.Tick += new System.EventHandler(this.CheckWoW);
            // 
            // LogDirectoryBrowser
            // 
            this.LogDirectoryBrowser.Description = "Выберите директорию для сохранения логов";
            this.LogDirectoryBrowser.SelectedPath = global::Nakamar.Properties.Settings.Default.LogDirectory;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(567, 344);
            this.Controls.Add(this.WPSLabel);
            this.Controls.Add(this.LogGroupBox);
            this.Controls.Add(this.AutoEnable);
            this.Controls.Add(this.DisableBotButton);
            this.Controls.Add(this.BotStateLabel);
            this.Controls.Add(this.EnableBotButton);
            this.DataBindings.Add(new System.Windows.Forms.Binding("Location", global::Nakamar.Properties.Settings.Default, "MainWindowLocation", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.Location = global::Nakamar.Properties.Settings.Default.MainWindowLocation;
            this.Name = "MainForm";
            this.Text = "Программа =)";
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainForm_FormClosing);
            this.LogGroupBox.ResumeLayout(false);
            this.LogGroupBox.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Timer SaveSettingsTimer;
        private System.Windows.Forms.Button EnableBotButton;
        private System.Windows.Forms.Label BotStateLabel;
        private System.Windows.Forms.Button DisableBotButton;
        private System.Windows.Forms.CheckBox AutoEnable;
        private System.Windows.Forms.GroupBox LogGroupBox;
        private System.Windows.Forms.ListBox LogBox;
        private System.Windows.Forms.Button ClearLogButton;
        private System.Windows.Forms.ToolTip Tooltip;
        private System.Windows.Forms.CheckBox AutoScrollCheckBox;
        private System.Windows.Forms.Timer Work;
        private System.Windows.Forms.Label WPSLabel;
        private System.Windows.Forms.Timer WPSTimer;
        private System.Windows.Forms.Timer WoWChecker;
        private System.Windows.Forms.CheckBox LogToFile;
        private System.Windows.Forms.Button ChangeLogDirectoryButton;
        private System.Windows.Forms.FolderBrowserDialog LogDirectoryBrowser;
    }
}

