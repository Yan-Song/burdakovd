namespace Plugins.AccountManager
{
    partial class EditProfile
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(EditProfile));
            this.OK = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.tableLayout = new System.Windows.Forms.TableLayoutPanel();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.ProfileName = new System.Windows.Forms.TextBox();
            this.AccountName = new System.Windows.Forms.TextBox();
            this.AccountPassword = new System.Windows.Forms.TextBox();
            this.Realm = new System.Windows.Forms.TextBox();
            this.Online24 = new System.Windows.Forms.Label();
            this.ProfileEnabled = new System.Windows.Forms.CheckBox();
            this.TimeSinceLastNTD = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.CharacterIndex = new System.Windows.Forms.NumericUpDown();
            this.tableLayout.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.CharacterIndex)).BeginInit();
            this.SuspendLayout();
            // 
            // OK
            // 
            this.OK.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.OK.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.OK.Location = new System.Drawing.Point(246, 272);
            this.OK.Name = "OK";
            this.OK.Size = new System.Drawing.Size(90, 30);
            this.OK.TabIndex = 0;
            this.OK.Text = "OK";
            this.OK.UseVisualStyleBackColor = true;
            this.OK.Click += new System.EventHandler(this.OK_Click);
            // 
            // button2
            // 
            this.button2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.button2.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.button2.Location = new System.Drawing.Point(342, 272);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(90, 30);
            this.button2.TabIndex = 1;
            this.button2.Text = "Отмена";
            this.button2.UseVisualStyleBackColor = true;
            // 
            // tableLayout
            // 
            this.tableLayout.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.tableLayout.ColumnCount = 2;
            this.tableLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayout.Controls.Add(this.label1, 0, 0);
            this.tableLayout.Controls.Add(this.label2, 0, 1);
            this.tableLayout.Controls.Add(this.label3, 0, 2);
            this.tableLayout.Controls.Add(this.label4, 0, 3);
            this.tableLayout.Controls.Add(this.label5, 0, 5);
            this.tableLayout.Controls.Add(this.label6, 0, 6);
            this.tableLayout.Controls.Add(this.ProfileName, 1, 0);
            this.tableLayout.Controls.Add(this.AccountName, 1, 1);
            this.tableLayout.Controls.Add(this.AccountPassword, 1, 2);
            this.tableLayout.Controls.Add(this.Realm, 1, 3);
            this.tableLayout.Controls.Add(this.Online24, 1, 5);
            this.tableLayout.Controls.Add(this.TimeSinceLastNTD, 1, 6);
            this.tableLayout.Controls.Add(this.label7, 0, 4);
            this.tableLayout.Controls.Add(this.CharacterIndex, 1, 4);
            this.tableLayout.Location = new System.Drawing.Point(14, 18);
            this.tableLayout.Name = "tableLayout";
            this.tableLayout.RowCount = 7;
            this.tableLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 14.2851F));
            this.tableLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 14.2851F));
            this.tableLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 14.2851F));
            this.tableLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 14.2851F));
            this.tableLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 14.28939F));
            this.tableLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 14.2851F));
            this.tableLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 14.28511F));
            this.tableLayout.Size = new System.Drawing.Size(418, 239);
            this.tableLayout.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Dock = System.Windows.Forms.DockStyle.Right;
            this.label1.Location = new System.Drawing.Point(123, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(76, 34);
            this.label1.TabIndex = 0;
            this.label1.Text = "Имя профиля";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Dock = System.Windows.Forms.DockStyle.Right;
            this.label2.Location = new System.Drawing.Point(73, 34);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(126, 34);
            this.label2.TabIndex = 1;
            this.label2.Text = "Имя аккаунта Battle.net";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Dock = System.Windows.Forms.DockStyle.Right;
            this.label3.Location = new System.Drawing.Point(97, 68);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(102, 34);
            this.label3.TabIndex = 2;
            this.label3.Text = "Пароль к аккаунту";
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Dock = System.Windows.Forms.DockStyle.Right;
            this.label4.Location = new System.Drawing.Point(126, 102);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(73, 34);
            this.label4.TabIndex = 3;
            this.label4.Text = "Игровой мир";
            this.label4.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // ProfileName
            // 
            this.ProfileName.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.ProfileName.Location = new System.Drawing.Point(205, 7);
            this.ProfileName.Name = "ProfileName";
            this.ProfileName.Size = new System.Drawing.Size(210, 20);
            this.ProfileName.TabIndex = 6;
            this.ProfileName.TextChanged += new System.EventHandler(this.NameChanged);
            // 
            // AccountName
            // 
            this.AccountName.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.AccountName.Location = new System.Drawing.Point(205, 41);
            this.AccountName.Name = "AccountName";
            this.AccountName.Size = new System.Drawing.Size(210, 20);
            this.AccountName.TabIndex = 7;
            this.AccountName.TextChanged += new System.EventHandler(this.ProfileChanged);
            // 
            // AccountPassword
            // 
            this.AccountPassword.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.AccountPassword.Location = new System.Drawing.Point(205, 75);
            this.AccountPassword.Name = "AccountPassword";
            this.AccountPassword.Size = new System.Drawing.Size(210, 20);
            this.AccountPassword.TabIndex = 8;
            this.AccountPassword.UseSystemPasswordChar = true;
            this.AccountPassword.TextChanged += new System.EventHandler(this.ProfileChanged);
            // 
            // Realm
            // 
            this.Realm.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.Realm.Location = new System.Drawing.Point(205, 109);
            this.Realm.Name = "Realm";
            this.Realm.Size = new System.Drawing.Size(210, 20);
            this.Realm.TabIndex = 9;
            this.Realm.TextChanged += new System.EventHandler(this.ProfileChanged);
            // 
            // Online24
            // 
            this.Online24.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.Online24.AutoSize = true;
            this.Online24.Location = new System.Drawing.Point(205, 180);
            this.Online24.Name = "Online24";
            this.Online24.Size = new System.Drawing.Size(35, 13);
            this.Online24.TabIndex = 10;
            this.Online24.Text = "label7";
            this.Online24.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // ProfileEnabled
            // 
            this.ProfileEnabled.AutoSize = true;
            this.ProfileEnabled.Location = new System.Drawing.Point(14, 323);
            this.ProfileEnabled.Name = "ProfileEnabled";
            this.ProfileEnabled.Size = new System.Drawing.Size(70, 17);
            this.ProfileEnabled.TabIndex = 3;
            this.ProfileEnabled.Text = "Включён";
            this.ProfileEnabled.UseVisualStyleBackColor = true;
            // 
            // TimeSinceLastNTD
            // 
            this.TimeSinceLastNTD.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.TimeSinceLastNTD.AutoSize = true;
            this.TimeSinceLastNTD.Location = new System.Drawing.Point(205, 215);
            this.TimeSinceLastNTD.Name = "TimeSinceLastNTD";
            this.TimeSinceLastNTD.Size = new System.Drawing.Size(35, 13);
            this.TimeSinceLastNTD.TabIndex = 11;
            this.TimeSinceLastNTD.Text = "label8";
            this.TimeSinceLastNTD.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Dock = System.Windows.Forms.DockStyle.Right;
            this.label5.Location = new System.Drawing.Point(19, 170);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(180, 34);
            this.label5.TabIndex = 4;
            this.label5.Text = "Был онлайн за последние 24 часа";
            this.label5.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Dock = System.Windows.Forms.DockStyle.Right;
            this.label6.Location = new System.Drawing.Point(3, 204);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(196, 35);
            this.label6.TabIndex = 5;
            this.label6.Text = "Время с последнего \"нечего делать\"";
            this.label6.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Dock = System.Windows.Forms.DockStyle.Right;
            this.label7.Location = new System.Drawing.Point(14, 136);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(185, 34);
            this.label7.TabIndex = 12;
            this.label7.Text = "Номер персонажа (начиная с нуля)";
            this.label7.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // numericUpDown1
            // 
            this.CharacterIndex.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.CharacterIndex.Location = new System.Drawing.Point(205, 143);
            this.CharacterIndex.Maximum = new decimal(new int[] {
            9,
            0,
            0,
            0});
            this.CharacterIndex.Name = "numericUpDown1";
            this.CharacterIndex.Size = new System.Drawing.Size(210, 20);
            this.CharacterIndex.TabIndex = 13;
            this.CharacterIndex.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // EditProfile
            // 
            this.AcceptButton = this.OK;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.button2;
            this.ClientSize = new System.Drawing.Size(444, 314);
            this.Controls.Add(this.ProfileEnabled);
            this.Controls.Add(this.tableLayout);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.OK);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "EditProfile";
            this.TopMost = true;
            this.tableLayout.ResumeLayout(false);
            this.tableLayout.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.CharacterIndex)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button OK;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.TableLayoutPanel tableLayout;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox ProfileName;
        private System.Windows.Forms.TextBox AccountName;
        private System.Windows.Forms.TextBox AccountPassword;
        private System.Windows.Forms.TextBox Realm;
        private System.Windows.Forms.Label Online24;
        private System.Windows.Forms.CheckBox ProfileEnabled;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label TimeSinceLastNTD;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.NumericUpDown CharacterIndex;
    }
}