using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Util;
using Plugins.Properties;

namespace Plugins.AccountManager
{
    public partial class ProfileManagement : Form
    {
        public ProfileManagement()
        {
            InitializeComponent();
            updateList();
        }

        /// <summary>
        /// обновляет список профилей из Settings
        /// </summary>
        private void updateList()
        {
            ProfileList.BeginUpdate();

            ProfileList.Items.Clear();

            ProfileList.Items.AddRange(Settings.Default.Profiles.Keys.ToArray());

            ProfileList.EndUpdate();

            ProfileList_SelectedIndexChanged();
        }

        private string GetFreeProfileName()
        {
            int number = 0;
            string ans;

            do
            {
                ++number;
                ans = "Профиль " + number.ToString();
            }
            while (Settings.Default.Profiles.Keys.Contains(ans));

            return ans;
        }

        private void Create_Click(object sender, EventArgs e)
        {
            string name = GetFreeProfileName();
            Settings.Default.Profiles.Add(name, new Profile());
            updateList();
            EditProfile(name);
        }

        private void EditProfile(string name)
        {
            var f = new AccountManager.EditProfile(name);

            f.ShowDialog();

            updateList();
        }

        private void Edit_Click(object sender, EventArgs e)
        {
            if (ProfileList.SelectedItem != null)
            {
                EditProfile(ProfileList.SelectedItem.ToString());
            }
        }

        private void Delete_Click(object sender, EventArgs e)
        {
            string name = ProfileList.SelectedItem.ToString();
            if (MessageBox.Show("Вы уверены, что хотите удалить профиль \"" + name + "\"?", "Удалить?",
                MessageBoxButtons.YesNo) == DialogResult.Yes)
            {
                Settings.Default.Profiles.Remove(name);
                updateList();
            }
        }

        private void ProfileList_SelectedIndexChanged(object sender, EventArgs e)
        {
            ProfileList_SelectedIndexChanged();
        }

        private void ProfileList_SelectedIndexChanged()
        {
            Edit.Enabled = Delete.Enabled = ProfileList.SelectedIndex != -1;
        }

        private void ProfileList_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            Edit_Click(sender, e);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            openFileDialog1.FileName = Settings.Default.ConfigWTF;

            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                Settings.Default.ConfigWTF = openFileDialog1.FileName;
                Settings.Default.Save();
            }
        }

    }
}
