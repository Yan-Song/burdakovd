namespace NakamarStates
{
    partial class NavigationSettings
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
            this.button1 = new System.Windows.Forms.Button();
            this.RefreshViewTimer = new System.Windows.Forms.Timer(this.components);
            this.MapGroup = new System.Windows.Forms.GroupBox();
            this.Calibration = new System.Windows.Forms.Button();
            this.SelectBackground = new System.Windows.Forms.Button();
            this.PaintBox = new System.Windows.Forms.Panel();
            this.MainToolTip = new System.Windows.Forms.ToolTip(this.components);
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.MapGroup.SuspendLayout();
            this.PaintBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(12, 12);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 0;
            this.button1.Text = "тест";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // RefreshViewTimer
            // 
            this.RefreshViewTimer.Interval = 1000;
            // 
            // MapGroup
            // 
            this.MapGroup.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.MapGroup.Controls.Add(this.Calibration);
            this.MapGroup.Controls.Add(this.SelectBackground);
            this.MapGroup.Controls.Add(this.PaintBox);
            this.MapGroup.Location = new System.Drawing.Point(12, 41);
            this.MapGroup.Name = "MapGroup";
            this.MapGroup.Size = new System.Drawing.Size(878, 404);
            this.MapGroup.TabIndex = 1;
            this.MapGroup.TabStop = false;
            this.MapGroup.Text = "Карта";
            // 
            // Calibration
            // 
            this.Calibration.Location = new System.Drawing.Point(112, 375);
            this.Calibration.Name = "Calibration";
            this.Calibration.Size = new System.Drawing.Size(101, 23);
            this.Calibration.TabIndex = 2;
            this.Calibration.Text = "Калибровка";
            this.Calibration.UseVisualStyleBackColor = true;
            // 
            // SelectBackground
            // 
            this.SelectBackground.Location = new System.Drawing.Point(6, 375);
            this.SelectBackground.Name = "SelectBackground";
            this.SelectBackground.Size = new System.Drawing.Size(100, 23);
            this.SelectBackground.TabIndex = 1;
            this.SelectBackground.Text = "Выбрать фон...";
            this.SelectBackground.UseVisualStyleBackColor = true;
            // 
            // PaintBox
            // 
            this.PaintBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.PaintBox.BackColor = System.Drawing.Color.Gray;
            this.PaintBox.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.PaintBox.Controls.Add(this.pictureBox1);
            this.PaintBox.Location = new System.Drawing.Point(6, 19);
            this.PaintBox.Name = "PaintBox";
            this.PaintBox.Size = new System.Drawing.Size(866, 350);
            this.PaintBox.TabIndex = 0;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(179, 79);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(100, 50);
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // NavigationSettings
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(902, 457);
            this.Controls.Add(this.MapGroup);
            this.Controls.Add(this.button1);
            this.Name = "NavigationSettings";
            this.Text = "NavigationSettings";
            this.Load += new System.EventHandler(this.NavigationSettings_Load);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.NavigationSettings_FormClosed);
            this.MapGroup.ResumeLayout(false);
            this.PaintBox.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Timer RefreshViewTimer;
        private System.Windows.Forms.GroupBox MapGroup;
        private System.Windows.Forms.Button SelectBackground;
        private System.Windows.Forms.Panel PaintBox;
        private System.Windows.Forms.Button Calibration;
        private System.Windows.Forms.ToolTip MainToolTip;
        private System.Windows.Forms.PictureBox pictureBox1;
    }
}