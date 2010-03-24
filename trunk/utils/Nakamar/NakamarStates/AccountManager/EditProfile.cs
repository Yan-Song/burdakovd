using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Plugins.Properties;
using Util;

namespace Plugins.AccountManager
{
    public partial class EditProfile : Form
    {
        private Profile newProfile;
        private string oldName;

        public EditProfile(string name)
        {
            InitializeComponent();
            newProfile = Settings.Default.Profiles[name];
            oldName = name;

            ProfileName.Text = name;
            AccountName.Text = newProfile.AccountName;
            AccountPassword.Text = newProfile.Password;
            Realm.Text = newProfile.Realm;
            CharacterIndex.Value = (decimal)newProfile.CharacterIndex;
            ProfileEnabled.Checked = newProfile.Enabled;

            fillStats();
            Validate();

            if (!OK.Enabled)
            {
                Settings.Default.Profiles.Remove(name);
            }
        }

        private void fillStats()
        {
            Online24.Text = FormatTimeSpan(TimeSpan.FromHours(newProfile.BottedLast24Hours()));

            TimeSpan since = newProfile.SinceLastNothingToDo();

            TimeSinceLastNTD.Text = since.TotalDays > 365 ? "много" : FormatTimeSpan(newProfile.SinceLastNothingToDo());
        }

        private new void Validate()
        {
            OK.Enabled = Valid();
        }


        private bool Valid()
        {
            return
                !string.IsNullOrEmpty(ProfileName.Text)
                &&
                (ProfileName.Text == oldName || !Settings.Default.Profiles.ContainsKey(ProfileName.Text))
                &&
                !string.IsNullOrEmpty(AccountName.Text)
                &&
                !string.IsNullOrEmpty(AccountPassword.Text)
                &&
                !string.IsNullOrEmpty(Realm.Text);
        }

        private void ProfileChanged(object sender, EventArgs e)
        {
            Validate();
        }

        private void OK_Click(object sender, EventArgs e)
        {
            newProfile.AccountName = AccountName.Text;
            newProfile.Password = AccountPassword.Text;
            newProfile.Realm = Realm.Text;
            newProfile.Enabled = ProfileEnabled.Checked;
            newProfile.CharacterIndex = (int)CharacterIndex.Value;

            if(Settings.Default.Profiles.ContainsKey(oldName))
            {
                Settings.Default.Profiles.Remove(oldName);
            }
            Settings.Default.Profiles.Add(ProfileName.Text, newProfile);
            Settings.Default.Save();
        }

        private void NameChanged(object sender, EventArgs e)
        {
            Text = ProfileName.Text;
            ProfileChanged(sender, e);
        }

        private static string FormatTimeSpan(TimeSpan span)
        {
            return span.Days.ToString("00") + " д., " +
                   span.Hours.ToString("00") + " ч., " +
                   span.Minutes.ToString("00") + " мин., " +
                   span.Seconds.ToString("00") + " сек.";
        }
    }
}
