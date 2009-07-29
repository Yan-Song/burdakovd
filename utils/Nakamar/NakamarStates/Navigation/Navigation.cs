using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FiniteStateMachine;
using NakamarStates.Properties;
using System.IO;
using System.Windows.Forms;
using WoWMemoryManager;

namespace NakamarStates
{
    public class Navigation : State
    {
        WayPointList WayPoints;
        Point Destination = null;

        public override void Configure()
        {
            SaveFileDialog Dialog = new SaveFileDialog();
            Dialog.AddExtension = true;
            Dialog.CheckFileExists = false;
            Dialog.CheckPathExists = true;
            Dialog.OverwritePrompt = false;
            Dialog.DefaultExt = "xml";
            Dialog.FileName = Settings.Default.WayPointsPath;
            Dialog.Filter = "Xml files (*.xml)|*.xml";
            Dialog.Title = "Выберите файл для зарузки и сохранения точек маршрута";

            if (Dialog.ShowDialog() == DialogResult.OK)
            {
                if (File.Exists(Dialog.FileName))
                {
                    DialogResult result = MessageBox.Show("Выбранный файл уже существует. Загрузить из него точки маршрута? " +
                        Environment.NewLine +
                        "В этом случае загруженные точки маршрута заменят текущий набор.",
                        "Файл уже существует",
                        MessageBoxButtons.YesNoCancel,
                        MessageBoxIcon.Question,
                        MessageBoxDefaultButton.Button1);

                    if (result == DialogResult.Cancel) return;

                    Settings.Default.WayPointsPath = Dialog.FileName;

                    if (result == DialogResult.Yes)
                        Load();
                    else
                        Save();
                }
                else
                {
                    Settings.Default.WayPointsPath = Dialog.FileName;
                    Save();
                }
            }
            Settings.Default.Save();
        }

        public Navigation(object machine, object memory) : base(machine, memory)
        {
            Load();
        }

        void Load()
        {
            try
            {
                WayPoints = new WayPointList(Settings.Default.WayPointsPath);
                Log("Загружено " + WayPoints.Count + " точек маршрута из " + Settings.Default.WayPointsPath);
            }
            catch (FileNotFoundException e)
            {
                LogError("Точки маршрута не загружены: " + e.Message);
                WayPoints = new WayPointList();
            }
        }

        void Save()
        {
            try
            {
                WayPoints.Save(Settings.Default.WayPointsPath);
                Log("Точки маршрута сохранены");
            }
            catch(Exception e)
            {
                LogError("Не удалось сохранить точки маршрута: " + e.Message);
            }
        }

        /// <summary>
        /// less than Relogger, but more than MessageScanner
        /// </summary>
        public override int Priority
        {
            get { return 1000; }
        }

        public override bool NeedToRun
        {
            get
            {
                if (Destination != null)
                    return true; // need to move
                if (!Memory.NewAddonMessage())
                    return false; // nothing to process
                string command = Memory.GetAddonMessage().command;
                return command == "waypoint" || command == "goto" || command == "break";
            }
        }

        public override void Run()
        {
            AddonMessage m = Memory.GetAddonMessage();

            if (Memory.NewAddonMessage())
            {
                if (m.command == "goto")
                {
                    SetDestination(m);
                    Memory.ProcessAddonMessage(m.id);
                }
                else if (m.command == "break" && Destination != null)
                {
                    Destination = null;
                    Log("Отменяю движение");
                    Memory.KB.KeyUpAll();
                    // do not ProcessAddonMessage(), because other states need to break too
                }
                else if (m.command == "waypoint")
                {
                    ManageWayPoints(m);
                }
            }
            else if (Destination != null)
            {
                Navigate();
            }
            else
                throw new Exception("o_O");

        }

        private void ManageWayPoints(AddonMessage m)
        {
            string command = m.arguments[0];
            if (command == "add")
                AddWayPoint(m);
            else if (command == "remove" || command == "delete")
                RemoveWayPoint(m);
            else if (command == "rename")
                RenameWayPoint(m);
            else
                throw new NotImplementedException(command);
        }

        private void RenameWayPoint(AddonMessage m)
        {
            throw new NotImplementedException();
        }

        private void RemoveWayPoint(AddonMessage m)
        {
            throw new NotImplementedException();
        }

        private void AddWayPoint(AddonMessage m)
        {
            WayPointType type = (WayPointType)Enum.Parse(typeof(WayPointType), m.arguments[1], true);
            string name;
            if (m.arguments.Length == 2)
                name = WayPoints.NewName();
            else
                name = m.arguments[2];
            if (type == WayPointType.Simple)
                AddSimpleWayPoint(name);
            else if (type == WayPointType.NPC)
                AddNPCWayPoint(name);
            else if (type == WayPointType.Mailbox)
                AddMailboxWayPoint(name);
            else
                throw new NotImplementedException();
        }

        private void AddMailboxWayPoint(string name)
        {
            throw new NotImplementedException();
        }

        private void AddNPCWayPoint(string name)
        {
            throw new NotImplementedException();
        }

        private void AddSimpleWayPoint(string name)
        {
            throw new NotImplementedException();
        }

        private void Navigate()
        {
            throw new NotImplementedException();
        }

        private void SetDestination(AddonMessage addonMessage)
        {
            throw new NotImplementedException();
        }
    }
}
