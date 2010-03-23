namespace Plugins.AccountManager
{
    partial class ProfileManagement
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ProfileManagement));
            this.ProfileList = new System.Windows.Forms.ListBox();
            this.Create = new System.Windows.Forms.Button();
            this.Edit = new System.Windows.Forms.Button();
            this.Delete = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.mainToolTip = new System.Windows.Forms.ToolTip(this.components);
            this.label3 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.InterestTime = new System.Windows.Forms.NumericUpDown();
            this.maxWorkHours = new System.Windows.Forms.NumericUpDown();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            ((System.ComponentModel.ISupportInitialize)(this.InterestTime)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.maxWorkHours)).BeginInit();
            this.SuspendLayout();
            // 
            // ProfileList
            // 
            this.ProfileList.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.ProfileList.FormattingEnabled = true;
            this.ProfileList.IntegralHeight = false;
            this.ProfileList.Location = new System.Drawing.Point(12, 12);
            this.ProfileList.Name = "ProfileList";
            this.ProfileList.Size = new System.Drawing.Size(282, 173);
            this.ProfileList.TabIndex = 0;
            this.ProfileList.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.ProfileList_MouseDoubleClick);
            this.ProfileList.SelectedIndexChanged += new System.EventHandler(this.ProfileList_SelectedIndexChanged);
            // 
            // Create
            // 
            this.Create.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.Create.Location = new System.Drawing.Point(300, 13);
            this.Create.Name = "Create";
            this.Create.Size = new System.Drawing.Size(120, 26);
            this.Create.TabIndex = 1;
            this.Create.Text = "Создать";
            this.Create.UseVisualStyleBackColor = true;
            this.Create.Click += new System.EventHandler(this.Create_Click);
            // 
            // Edit
            // 
            this.Edit.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.Edit.Location = new System.Drawing.Point(300, 45);
            this.Edit.Name = "Edit";
            this.Edit.Size = new System.Drawing.Size(120, 26);
            this.Edit.TabIndex = 2;
            this.Edit.Text = "Изменить";
            this.Edit.UseVisualStyleBackColor = true;
            this.Edit.Click += new System.EventHandler(this.Edit_Click);
            // 
            // Delete
            // 
            this.Delete.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.Delete.Location = new System.Drawing.Point(300, 77);
            this.Delete.Name = "Delete";
            this.Delete.Size = new System.Drawing.Size(120, 26);
            this.Delete.TabIndex = 3;
            this.Delete.Text = "Удалить";
            this.Delete.UseVisualStyleBackColor = true;
            this.Delete.Click += new System.EventHandler(this.Delete_Click);
            // 
            // label1
            // 
            this.label1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(36, 229);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(206, 13);
            this.label1.TabIndex = 6;
            this.label1.Text = "Максимальное время ботания, в часах";
            this.mainToolTip.SetToolTip(this.label1, resources.GetString("label1.ToolTip"));
            // 
            // label2
            // 
            this.label2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(7, 255);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(235, 13);
            this.label2.TabIndex = 7;
            this.label2.Text = "Время устаревания \"нечего делать\", в часах";
            this.mainToolTip.SetToolTip(this.label2, "Этот параметр влияет на частоту переключений между профилями, когда все профили у" +
                    "же выложили весь товар на аукцион и им \"нечего делать\".");
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 202);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(90, 13);
            this.label3.TabIndex = 8;
            this.label3.Text = "Путь к Config.wtf";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(262, 195);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(32, 23);
            this.button1.TabIndex = 10;
            this.button1.Text = "...";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // textBox1
            // 
            this.textBox1.DataBindings.Add(new System.Windows.Forms.Binding("Text", global::Plugins.Properties.Settings.Default, "ConfigWTF", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.textBox1.Location = new System.Drawing.Point(108, 198);
            this.textBox1.Name = "textBox1";
            this.textBox1.ReadOnly = true;
            this.textBox1.Size = new System.Drawing.Size(148, 20);
            this.textBox1.TabIndex = 9;
            this.textBox1.Text = global::Plugins.Properties.Settings.Default.ConfigWTF;
            // 
            // InterestTime
            // 
            this.InterestTime.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.InterestTime.DataBindings.Add(new System.Windows.Forms.Binding("Value", global::Plugins.Properties.Settings.Default, "HowOldHoursNTDIsInteresting", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.InterestTime.Location = new System.Drawing.Point(248, 253);
            this.InterestTime.Maximum = new decimal(new int[] {
            24,
            0,
            0,
            0});
            this.InterestTime.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.InterestTime.Name = "InterestTime";
            this.InterestTime.Size = new System.Drawing.Size(46, 20);
            this.InterestTime.TabIndex = 5;
            this.mainToolTip.SetToolTip(this.InterestTime, "Этот параметр влияет на частоту переключений между профилями, когда все профили у" +
                    "же выложили весь товар на аукцион и им \"нечего делать\".");
            this.InterestTime.Value = global::Plugins.Properties.Settings.Default.HowOldHoursNTDIsInteresting;
            // 
            // maxWorkHours
            // 
            this.maxWorkHours.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.maxWorkHours.DataBindings.Add(new System.Windows.Forms.Binding("Value", global::Plugins.Properties.Settings.Default, "HowMuchHoursAllowedToBotEvery24Hours", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.maxWorkHours.Location = new System.Drawing.Point(248, 227);
            this.maxWorkHours.Maximum = new decimal(new int[] {
            24,
            0,
            0,
            0});
            this.maxWorkHours.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.maxWorkHours.Name = "maxWorkHours";
            this.maxWorkHours.Size = new System.Drawing.Size(46, 20);
            this.maxWorkHours.TabIndex = 4;
            this.mainToolTip.SetToolTip(this.maxWorkHours, resources.GetString("maxWorkHours.ToolTip"));
            this.maxWorkHours.Value = global::Plugins.Properties.Settings.Default.HowMuchHoursAllowedToBotEvery24Hours;
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.DefaultExt = "wtf";
            this.openFileDialog1.Filter = "Warcraft Text Files|*.wtf|Все файлы|*.*";
            // 
            // ProfileManagement
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(427, 285);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.InterestTime);
            this.Controls.Add(this.maxWorkHours);
            this.Controls.Add(this.Delete);
            this.Controls.Add(this.Edit);
            this.Controls.Add(this.Create);
            this.Controls.Add(this.ProfileList);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "ProfileManagement";
            this.Text = "Управление профилями";
            this.TopMost = true;
            ((System.ComponentModel.ISupportInitialize)(this.InterestTime)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.maxWorkHours)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox ProfileList;
        private System.Windows.Forms.Button Create;
        private System.Windows.Forms.Button Edit;
        private System.Windows.Forms.Button Delete;
        private System.Windows.Forms.NumericUpDown maxWorkHours;
        private System.Windows.Forms.NumericUpDown InterestTime;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ToolTip mainToolTip;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
    }
}