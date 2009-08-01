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
using Util;

namespace NakamarStates
{
    public class Navigation : State
    {
        WayPointSet Destinations;
        DestinationPoint Destination = null;

        PlayerPoint Me
        {
            get
            {
                var player = Memory.ObjectManager.LocalPlayer;
                return new PlayerPoint(player.XPosition, player.YPosition, player.ZPosition);
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
                Destinations = new WayPointSet(Settings.Default.WayPointsPath);
                Log("Загружено " + Destinations.Count + " точек маршрута из " + Settings.Default.WayPointsPath);
            }
            catch (FileNotFoundException e)
            {
                LogError("Точки маршрута не загружены: " + e.Message);
                Destinations = new WayPointSet();
            }
        }

        void Save()
        {
            try
            {
                Destinations.Save(Settings.Default.WayPointsPath);
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
                return command == "destination" || command == "goto" || command == "break" || command == "route";
            }
        }

        public override void Run()
        {
            AddonMessage m = Memory.GetAddonMessage();

            if (Memory.NewAddonMessage())
            {
                if (m.command == "goto")
                {
                    MakeRoute(m);
                    Memory.ProcessAddonMessage(m.id);
                }
                else if (m.command == "break" && Destination != null)
                {
                    Destination = null;
                    Log("Отменяю движение");
                    Memory.KB.KeyUpAll();
                    // do not ProcessAddonMessage(), because other states need to break too
                }
                else if (m.command == "destination")
                {
                    ManageDestinations(m);
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

        private void MakeRoute(AddonMessage m)
        {
            throw new NotImplementedException();
        }

        private void ManageRoutes(AddonMessage m)
        {
            string command = m.argument(0);
            if (command == null)
                LogError("нужно указать субкоманду begin|point|commit");
            else if (command == "begin")
                BeginRoute(m);
            else if (command == "point")
                AddPointInRoute();
            else if (command == "commit")
                CommitRoute();
            else
                throw new NotImplementedException(command);
        }

        private void BeginRoute(AddonMessage m)
        {
            throw new NotImplementedException();
        }

        private void AddPointInRoute()
        {
            throw new NotImplementedException();
        }

        private void CommitRoute()
        {
            throw new NotImplementedException();
        }

        private void ManageDestinations(AddonMessage m)
        {
            string command = m.argument(0);
            if (command == null)
                LogError("нужно указать субкоманду");
            else if (command == "add")
                AddDestination(m);
            else if (command == "info")
                ShowInfo(m);
            else
                throw new NotImplementedException(command);
        }

        /// <summary>
        /// destination;info;all (default)
        /// destination;info;nearest
        /// destination;info;DestinationPointName
        /// </summary>
        /// <param name="m"></param>
        private void ShowInfo(AddonMessage m)
        {
            string name = m.argument(1, "all");
            if (name == "nearest")
            {
                Log("Информация о ближайшей точке:");
                ShowInfo(GetNearestDestinationPoint());
            }
            else if (name == "all")
            {
                Log("Информация о всех точках:");
                foreach (DestinationPoint p in Destinations.Values)
                    ShowInfo(p);
            }
            else
            {
                Log("Информация о " + name + ":");
                ShowInfo(Destinations[name]);
            }
        }

        private void ShowInfo(DestinationPoint p)
        {
            Log("  " + p.Name + "(x = " + p.X + "; y = " + p.Y + "; z = " + p.Z +
                "; distance = " + Me.Distance(p) + "; angle = " + Me.Angle(p) +
                "; relativeAngle = " + Me.RelativeAngle(Memory.ObjectManager.LocalPlayer.Rotation, p));
        }

        private DestinationPoint GetNearestDestinationPoint()
        {
            DestinationPoint nearest = null;
            double minDistance = double.MaxValue;
            foreach(DestinationPoint p in Destinations.Values)
                if (Me.Distance(p) < minDistance)
                {
                    nearest = p;
                    minDistance = Me.Distance(p);
                }
            if (nearest == null)
                throw new Exception("there is no points");
            return nearest;
        }

        /// <summary>
        /// destination;add;Type[;Name[;Tag]]
        /// </summary>
        /// <param name="m"></param>
        private void AddDestination(AddonMessage m)
        {
            WayPointType type = (WayPointType)Enum.Parse(typeof(WayPointType), m.argument(1, "Simple"), true);

            try
            {
                DestinationPoint point;
                if (type == WayPointType.Simple)
                    point = NewSimpleDestination(m.argument(2), m.argument(3)); // name, tag
                else if (type == WayPointType.Mailbox)
                    point = NewMailboxDestination(m.argument(2), m.argument(3)); // name, tag
                else if (type == WayPointType.NPC)
                    point = NewNPCDestination(m.argument(2)); // tag
                else
                    throw new NotImplementedException(type.ToString());

                Destinations.Add(point);
                Log("Добавлена  " + point.ToString() + ", расстояние до неё: " + Me.Distance(point));
                Destinations.Save(Settings.Default.WayPointsPath);

            }
            catch (Exception e)
            {
                LogError("Не удалось добавить точку маршрута: " + e);
            }
        }

        private DestinationPoint NewNPCDestination(string tag)
        {
            try
            {
                NpcObject target = (NpcObject)Memory.ObjectManager.ByGuid(Memory.ObjectManager.LocalPlayer.TargetGuid);
                return new DestinationPoint(target.Name, WayPointType.NPC, tag ?? "",
                    target.XPosition, target.YPosition, target.ZPosition);
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

        private DestinationPoint NewMailboxDestination(string name, string tag)
        {
            IEnumerable<GameObject> mailboxes = Memory.ObjectManager.GameObjects.Where(g => g.Name == name);
            
            GameObject nearestMailbox =
                mailboxes.OrderBy(g => Me.Distance(g.XPosition, g.YPosition, g.ZPosition)).Single();

            return new DestinationPoint(name ?? Destinations.NewName(), WayPointType.Mailbox, tag ?? "",
                nearestMailbox.XPosition, nearestMailbox.YPosition, nearestMailbox.ZPosition);
        }

        private DestinationPoint NewSimpleDestination(string name, string tag)
        {
            var player = Memory.ObjectManager.LocalPlayer;
            return new DestinationPoint(name ?? Destinations.NewName(), WayPointType.Simple, tag ?? "",
                player.XPosition, player.YPosition, player.ZPosition);
        }

        private void Navigate()
        {
            throw new NotImplementedException();
        }

        private void MakeRoute(string destination)
        {
            throw new NotImplementedException();
        }
    }
}
