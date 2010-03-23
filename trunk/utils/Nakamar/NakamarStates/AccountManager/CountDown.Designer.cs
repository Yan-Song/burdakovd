namespace Plugins.AccountManager
{
    partial class CountDown
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CountDown));
            this.OK = new System.Windows.Forms.Button();
            this.Options = new System.Windows.Forms.Button();
            this.MessageBox = new System.Windows.Forms.TextBox();
            this.CountDownTimer = new System.Windows.Forms.Timer(this.components);
            this.doNotShowThisWindow = new System.Windows.Forms.CheckBox();
            this.mainToolTip = new System.Windows.Forms.ToolTip(this.components);
            this.SuspendLayout();
            // 
            // OK
            // 
            this.OK.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.OK.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.OK.Location = new System.Drawing.Point(346, 170);
            this.OK.Name = "OK";
            this.OK.Size = new System.Drawing.Size(90, 30);
            this.OK.TabIndex = 0;
            this.OK.Tag = "";
            this.OK.Text = "OK";
            this.OK.UseVisualStyleBackColor = true;
            // 
            // Options
            // 
            this.Options.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.Options.Location = new System.Drawing.Point(442, 170);
            this.Options.Name = "Options";
            this.Options.Size = new System.Drawing.Size(90, 30);
            this.Options.TabIndex = 1;
            this.Options.Text = "Параметры...";
            this.Options.UseVisualStyleBackColor = true;
            this.Options.Click += new System.EventHandler(this.Options_Click);
            // 
            // MessageBox
            // 
            this.MessageBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.MessageBox.BackColor = System.Drawing.SystemColors.Control;
            this.MessageBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.MessageBox.Location = new System.Drawing.Point(12, 12);
            this.MessageBox.Multiline = true;
            this.MessageBox.Name = "MessageBox";
            this.MessageBox.ReadOnly = true;
            this.MessageBox.Size = new System.Drawing.Size(520, 152);
            this.MessageBox.TabIndex = 2;
            this.MessageBox.TabStop = false;
            this.MessageBox.Enter += new System.EventHandler(this.MessageBox_Enter);
            // 
            // CountDownTimer
            // 
            this.CountDownTimer.Enabled = true;
            this.CountDownTimer.Interval = 1000;
            this.CountDownTimer.Tick += new System.EventHandler(this.CountDownTimer_Tick);
            // 
            // doNotShowThisWindow
            // 
            this.doNotShowThisWindow.AutoSize = true;
            this.doNotShowThisWindow.Location = new System.Drawing.Point(12, 178);
            this.doNotShowThisWindow.Name = "doNotShowThisWindow";
            this.doNotShowThisWindow.Size = new System.Drawing.Size(245, 17);
            this.doNotShowThisWindow.TabIndex = 3;
            this.doNotShowThisWindow.Text = "Не показывать это окно в текущей сессии";
            this.mainToolTip.SetToolTip(this.doNotShowThisWindow, "Если установить флажок, то это окно не будет отображаться пока не перезапустишь п" +
                    "рограмму.");
            this.doNotShowThisWindow.UseVisualStyleBackColor = true;
            this.doNotShowThisWindow.CheckedChanged += new System.EventHandler(this.doNotShowThisWindow_CheckedChanged);
            // 
            // CountDown
            // 
            this.AcceptButton = this.OK;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.OK;
            this.ClientSize = new System.Drawing.Size(544, 212);
            this.Controls.Add(this.doNotShowThisWindow);
            this.Controls.Add(this.MessageBox);
            this.Controls.Add(this.Options);
            this.Controls.Add(this.OK);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "CountDown";
            this.Text = "Выбор профиля";
            this.TopMost = true;
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button OK;
        private System.Windows.Forms.Button Options;
        private System.Windows.Forms.TextBox MessageBox;
        private System.Windows.Forms.Timer CountDownTimer;
        private System.Windows.Forms.ToolTip mainToolTip;
        internal System.Windows.Forms.CheckBox doNotShowThisWindow;
    }
}