using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FiniteStateMachine;
using NakamarStates.Properties;
using System.IO;
using System.Windows.Forms;
using WoWMemoryManager;
using WoWMemoryManager.WoWObject;

namespace NakamarStates
{
    public class Navigation : State
    {
        WayPointList WayPoints;
        Point Destination = null;

        Point Me
        {
            get
            {
                var player = Memory.ObjectManager.LocalPlayer;
                return new Point(player.XPosition, player.YPosition, player.ZPosition);
            }
        }

        public override void Configure()
        {
            ConfigureWayPointsPath();
        }

        public void ConfigureWayPointsPath()
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
                return command == "waypoint" || command == "goto" || command == "break" || command == "route";
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
                    Memory.ProcessAddonMessage(m.id);
                }
                else if (m.command == "route")
                {
                    ManageRoutes(m);
                    Memory.ProcessAddonMessage(m.id);
                }
            }
            else if (Destination != null)
            {
                Navigate();
            }
            else
                throw new Exception("o_O");

        }

        private void SetDestination(AddonMessage m)
        {
            throw new NotImplementedException();
        }

        private void ManageRoutes(AddonMessage m)
        {
            throw new NotImplementedException();
        }

        private void ManageWayPoints(AddonMessage m)
        {
            string command = m.argument(0);
            if (command == null)
                LogError("нужно указать add|remove|rename");
            else if (command == "add")
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

        /// <summary>
        /// waypoint;add;Type[;Name[;Tag]]
        /// </summary>
        /// <param name="m"></param>
        private void AddWayPoint(AddonMessage m)
        {
            WayPointType type = (WayPointType)Enum.Parse(typeof(WayPointType), m.argument(1, "Simple"), true);

            try
            {
                Point point;
                if (type == WayPointType.Simple)
                    point = NewSimpleWayPoint(m.argument(2), m.argument(3)); // name, tag
                else if (type == WayPointType.Mailbox)
                    point = NewMailboxWayPoint(m.argument(3), m.argument(3)); // name, tag
                else if (type == WayPointType.NPC)
                    point = NewNPCWayPoint(m.argument(2)); // tag
                else
                    throw new NotImplementedException(type.ToString());

                WayPoints.Add(point);
                Log("Добавлена  " + point.ToString() + ", расстояние до неё: " + Me.Distance(point));
                WayPoints.Save(Settings.Default.WayPointsPath);

            }
            catch (Exception e)
            {
                LogError("Не удалось добавить точку маршрута: " + e);
            }
        }

        private Point NewNPCWayPoint(string tag)
        {
            try
            {
                NpcObject target = (NpcObject)Memory.ObjectManager.ByGuid(Memory.ObjectManager.LocalPlayer.TargetGuid);
                return new Point(target.Name, WayPointType.NPC, tag ?? "", target.XPosition, target.YPosition, target.ZPosition);
            }
            catch (KeyNotFoundException)
            {
                throw new Exception("Необходимо выбрать NPC");
            }
            catch (InvalidCastException)
            {
                throw new Exception("Необходимо выбрать именно NPC");
            }
        }

        private Point NewMailboxWayPoint(string name, string tag)
        {
            IEnumerable<GameObject> mailboxes = Memory.ObjectManager.GameObjects.Where(g => g.Name == "Mailbox");
            
            GameObject nearestMailbox =
                mailboxes.OrderBy(g => Me.Distance(g.XPosition, g.YPosition, g.ZPosition)).Single();

            return new Point(name ?? WayPoints.NewName(), WayPointType.Mailbox, tag ?? "",
                nearestMailbox.XPosition, nearestMailbox.YPosition, nearestMailbox.ZPosition);
        }

        private Point NewSimpleWayPoint(string name, string tag)
        {
            var player = Memory.ObjectManager.LocalPlayer;
            return new Point(name ?? WayPoints.NewName(), WayPointType.Simple, tag ?? "",
                player.XPosition, player.YPosition, player.ZPosition);
        }

        private void Navigate()
        {
            throw new NotImplementedException();
        }

        private void SetDestination(string destination)
        {
            throw new NotImplementedException();
        }
    }
}
