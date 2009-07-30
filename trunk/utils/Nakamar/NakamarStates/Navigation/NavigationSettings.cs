using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace NakamarStates
{
    public partial class NavigationSettings : Form
    {
        public NavigationSettings()
        {
            InitializeComponent();
        }

        private void NavigationSettings_Load(object sender, EventArgs e)
        {
            MainToolTip.
            RefreshViewTimer.Enabled = true;
        }

        private void NavigationSettings_FormClosed(object sender, FormClosedEventArgs e)
        {
            RefreshViewTimer.Enabled = false;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            
        }
    }
}
