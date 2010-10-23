using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FiniteStateMachine;
using Plugins.Properties;
using System.IO;
using System.Windows.Forms;
using WoWMemoryManager;
using WoWMemoryManager.WoWObject;
using Util;
using System.Collections;
using System.Windows.Input;
using System.Threading;

namespace Plugins
{
    enum TurningState
    {
        Left, Right, None
    }

    enum InteractResult
    {
        Success, Failed, Wait, SureSuccess
    }

    public class Navigation : State
    {
        private const double
            // максимальный угол между текущим и необходимым Rotation, при котором ещё можно идти вперёд
            MoveMaxAngle = Math.PI / 3,
            // минимальный угол -->>--, при котором уже можно жать кнопки поворота
            TurnMinAngle = Math.PI / 9;

        WayPointSet Destinations;
        Queue<WayPoint> MovementQueue = null;
        Route creatingRoute = null;

        bool CurrentMovementState = false;
        TurningState CurrentTurningState = TurningState.None;

        public PlayerPoint Me
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
                Log("Загружено " + Destinations.Count + " точек и " + Destinations.RoutesCount + " маршрутов из " + Settings.Default.WayPointsPath);
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
                if (!Memory.IsWoWForeground())
                {
                    StopNavigation();
                    return false;
                }
                if (MovementQueue != null)
                    return true; // need to move
                if (!Memory.NewAddonMessage())
                    return false; // nothing to process
                string command = Memory.GetAddonMessage().Command;
                return command == "destination" || command == "goto" || command == "break" || command == "route";
            }
        }

        public override void Run()
        {
            AddonMessage m = Memory.GetAddonMessage();

            if (Memory.NewAddonMessage())
            {
                if (m.Command == "goto")
                {
                    MakeRoute(m);
                    Memory.ProcessAddonMessage(m.Id);
                }
                else if (m.Command == "break" && MovementQueue != null)
                {
                    StopNavigation();
                }
                else if (m.Command == "destination")
                {
                    ManageDestinations(m);
                    Memory.ProcessAddonMessage(m.Id);
                }
                else if (m.Command == "route")
                {
                    ManageRoutes(m);
                    Memory.ProcessAddonMessage(m.Id);
                }
            }
            else if (MovementQueue != null)
            {
                Navigate();
            }
            else
                throw new Exception("o_O");

        }

        private void MakeRoute(AddonMessage m)
        {
            string query = m.Argument(0);
            if (query == null)
                throw new Exception("Куда идти?");
            MakeRoute(query);
        }

        /// <summary>
        /// ищет ближайший отрезок маршрута,  затем идёт по этому маршруту до ближайшей точки назначения
        /// </summary>
        /// <returns></returns>
        private IEnumerable<WayPoint> RouteToSomeDestinationPoint()
        {
            WayPoint secondPointOfNearestSegment = null;
            Route nearestRoute = null;
            double minDistance = double.MaxValue;

            foreach (var routes in Destinations.Routes.Values)
                foreach (Route route in routes)
                {
                    WayPoint previous = Destinations[route.From];
                    List<WayPoint> points = new List<WayPoint>(route.Points);
                    points.Add(Destinations[route.To]);

                    foreach (WayPoint point in points)
                    {
                        double distance = Me.Distance(previous, point);
                        if (distance < minDistance)
                        {
                            minDistance = distance;
                            secondPointOfNearestSegment = point;
                            nearestRoute = route;
                        }
                        previous = point;
                    }
                }

            Log("Расстояние до ближайшего маршрута: " + minDistance);

            Queue<WayPoint> q = new Queue<WayPoint>(nearestRoute.Points);
            q.Enqueue(Destinations[nearestRoute.To]);

            while (q.Peek() != secondPointOfNearestSegment)
                q.Dequeue();

            return q;
        }

        private void ManageRoutes(AddonMessage m)
        {
            try
            {
                string command = m.Argument(0);
                if (command == null)
                    LogError("нужно указать субкоманду begin|point|commit");
                else if (command == "begin")
                    BeginRoute(m);
                else if (command == "point")
                    AddPointInRoute();
                else if (command == "commit")
                    CommitRoute(m);
                else
                    throw new NotImplementedException(command);
            }
            catch (Exception e)
            {
                LogError("Исключение при работе с маршрутами: " + e);
            }
        }

        private void BeginRoute(AddonMessage m)
        {
            DestinationPoint from = Destinations[m.Argument(1)];
            string name = m.Argument(2) ?? Destinations.NewRouteName();

            creatingRoute = new Route(name);
            creatingRoute.From = from.Name;

            Log("Начинаю создавать новый маршрут: " + name);
            Log("Начальная точка: " + from);
        }

        private void AddPointInRoute()
        {
            var player = Memory.ObjectManager.LocalPlayer;
            WayPoint current = new WayPoint(player.XPosition, player.YPosition, player.ZPosition);
            creatingRoute.Points.Add(current);
            WayPoint prev = creatingRoute.Points.Count < 2 ?
                Destinations[creatingRoute.From] :
                creatingRoute.Points[creatingRoute.Points.Count-2];
            Log("В " + creatingRoute.Name + " добавлена точка №" + creatingRoute.Points.Count +
                " (" + current.X + "; " + current.Y + "; " + current.Z + ")" +
                ", расстояние от предыдущей точки: " + prev.Distance(current));
        }

        private void CommitRoute(AddonMessage m)
        {
            DestinationPoint to = Destinations[m.Argument(1)];

            creatingRoute.To = to.Name;

            Destinations.Add(creatingRoute);

            Log("Добавлен новый маршрут: '" + creatingRoute.Name);
            Log("Количество промежуточных точек: " + creatingRoute.Points.Count);
            Log("Общая длина маршрута: " + creatingRoute.TotalLength(Destinations));
            Log("Исходная точка: " + Destinations[creatingRoute.From]);
            Log("Конечная точка: " + Destinations[creatingRoute.To]);

            creatingRoute = null;

            Save();
        }

        private void ManageDestinations(AddonMessage m)
        {
            string command = m.Argument(0);
            if (command == null)
                LogError("нужно указать субкоманду add|info");
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
            string name = m.Argument(1, "all");
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
            WayPointType type = (WayPointType)Enum.Parse(typeof(WayPointType), m.Argument(1, "Simple"), true);

            try
            {
                DestinationPoint point;
                if (type == WayPointType.Simple)
                    point = NewSimpleDestination(m.Argument(2), m.Argument(3)); // name, tag
                else if (type == WayPointType.Mailbox)
                    point = NewMailboxDestination(m.Argument(2), m.Argument(3)); // name, tag
                else if (type == WayPointType.NPC)
                    point = NewNPCDestination(m.Argument(2)); // tag
                else
                    throw new NotImplementedException(type.ToString());

                Destinations.Add(point);
                Log("Добавлена  " + point.ToString() + ", расстояние до неё: " + Me.Distance(point));
                Save();

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
                NpcObject target = Memory.ObjectManager.ByName(Memory.TargetName);
                return new DestinationPoint(Memory.GetAddonMessage().Target, WayPointType.NPC, tag ?? "",
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
                mailboxes.OrderBy(g => Me.Distance(g.XPosition, g.YPosition, g.ZPosition)).First();

            return new DestinationPoint(name, WayPointType.Mailbox, tag ?? "",
                nearestMailbox.XPosition, nearestMailbox.YPosition, nearestMailbox.ZPosition);
        }

        private DestinationPoint NewSimpleDestination(string name, string tag)
        {
            var player = Memory.ObjectManager.LocalPlayer;
            return new DestinationPoint(name ?? Destinations.NewName("XYZ"), WayPointType.Simple, tag ?? "",
                player.XPosition, player.YPosition, player.ZPosition);
        }

        private void Navigate()
        {
            WayPoint current = MovementQueue.Peek();
            PlayerObject player = Memory.ObjectManager.LocalPlayer;

            if (current.InRange2D(Me)) // подошли к некоторой точке маршрута
                if (MovementQueue.Count == 1)
                {
                    SetMovementState(false);
                    SetTurningState(TurningState.None);
                    DoInteract((DestinationPoint)current);
                }
                else
                {
                    //Log("Переход к следующей точке маршрута");
                    MovementQueue.Dequeue();
                }
            else
            {
                // двигаемся

                AntiStuck();
                if (MovementQueue == null)
                    return;

                RandomJump();

                double relativeAngle = Me.RelativeAngle(player.Rotation, current);
                SetMovementState(Math.Abs(relativeAngle) < MoveMaxAngle);
                SetTurningState(relativeAngle);
            }
        }

        DateTime lastRandomJumpDecisionTime = DateTime.Now;

        private void RandomJump()
        {
            if (!CurrentMovementState)
                return;
            if ((DateTime.Now - lastRandomJumpDecisionTime).TotalSeconds < 1)
                return;

            lastRandomJumpDecisionTime = DateTime.Now;

            if ((new Random()).Next(1, 10) == 1)
                Jump();
        }

        DateTime LastJumped = new DateTime(0),
            LastTimeChecked = new DateTime(0),
            LastTimeChecked10 = new DateTime(0);
        WayPoint rememberedWaypoint;
        double lastDistance;
        double lastDistance10;
        DateTime LastStuck = DateTime.MinValue;
        private void AntiStuck()
        {
            if (rememberedWaypoint != MovementQueue.Peek())
            {
                LastTimeChecked = LastTimeChecked10 = DateTime.Now;
                rememberedWaypoint = MovementQueue.Peek();
                lastDistance = lastDistance10 = Me.Distance(rememberedWaypoint);
            }

            if(!CurrentMovementState)
            {
                LastTimeChecked = DateTime.Now;
                lastDistance = Me.Distance(rememberedWaypoint);
            }

            // за последние 0.5 секунды
            if ((DateTime.Now - LastTimeChecked).TotalSeconds > 0.5)
            {
                if (lastDistance - Me.Distance(rememberedWaypoint) > 1) // за последние полсекунды прошли более 1, сбрасываем
                {
                    lastDistance = Me.Distance(rememberedWaypoint);
                    LastTimeChecked = DateTime.Now;
                }
                else // возможно застрял
                {
                    if ((DateTime.Now - LastJumped).TotalSeconds > 0.5) // за последние полсекунды не прыгали
                    {
                        //Log("застрял? попробую попрыгать");
                        Jump();
                        LastJumped = DateTime.Now;
                    }
                }
            }

            // за последние 10 секунд
            if ((DateTime.Now - LastTimeChecked10).TotalSeconds > 10)
            {
                if (lastDistance10 - Me.Distance(rememberedWaypoint) > 1) // за последние 10 секунд прошли более 1, сбрасываем
                {
                    lastDistance10 = Me.Distance(rememberedWaypoint);
                    LastTimeChecked10 = DateTime.Now;
                }
                else // точно застрял
                {
                    Log("Совсем застрял!!! Делаю скриншот");
                    Memory.KeyBoard.PressKey(KeyBindings.PrintScreen, true);
                    Thread.Sleep(1000);

                    if (DateTime.Now - LastStuck < TimeSpan.FromMinutes(5))
                    {
                        Log("Застрял дважды в течение пяти минут");
                        Log("Закрываю всё.");
                        StopNavigation();
                        Machine.DoNotRestart = true;
                        Memory.StopWoW();
                        Machine.StopEngineByWorker();
                    }
                    else
                    {
                        LastStuck = DateTime.Now;

                        // запоминаем точку назначения и делаем паузу
                        Log("Пауза...");
                        DestinationPoint destination = (DestinationPoint)MovementQueue.Last();
                        StopNavigation();
                        Thread.Sleep(5000);

                        Log("Строим маршрут заново, возможно поблизости есть rescue point");
                        MakeRoute(destination.Name);   
                    }
                }
            }
        }

        private void Jump()
        {
            Memory.KeyBoard.PressKey(KeyBindings.Jump, false);
        }

        private void SetTurningState(double relativeAngle, double turnMinAngle)
        {
            double a = Math.Abs(relativeAngle);

            if (a > turnMinAngle)
                if (relativeAngle > 0)
                    SetTurningState(TurningState.Left);
                else
                    SetTurningState(TurningState.Right);
            else
                SetTurningState(TurningState.None);
        }

        private void SetTurningState(double relativeAngle)
        {
            SetTurningState(relativeAngle, TurnMinAngle);
        }

        private void SetTurningState(TurningState turningState)
        {
            if (turningState == CurrentTurningState) return;

            //Log("TurningState = " + turningState);

            // отменяем предыдущий поворот если он был
            if (CurrentTurningState == TurningState.Left)
                Memory.KeyBoard.KeyUp(KeyBindings.TurnLeft, false);
            else if (CurrentTurningState == TurningState.Right)
                Memory.KeyBoard.KeyUp(KeyBindings.TurnRight, false);

            // делаем новый если не None
            if (turningState == TurningState.Left)
                Memory.KeyBoard.KeyDown(KeyBindings.TurnLeft, false);
            else if (turningState == TurningState.Right)
                Memory.KeyBoard.KeyDown(KeyBindings.TurnRight, false);

            CurrentTurningState = turningState;
        }

        private void SetMovementState(bool isMoving)
        {
            if(isMoving != CurrentMovementState)
            {
                CurrentMovementState = isMoving;
                if (isMoving)
                {
                    //Log("startMovement");
                    Memory.KeyBoard.KeyDown(KeyBindings.MoveForward, false);
                }
                else
                {
                    //Log("stopMovement");
                    Memory.KeyBoard.KeyUp(KeyBindings.MoveForward, false);
                }
            }
        }

        private InteractResult InteractWithXYZ(DestinationPoint point)
        {
            return InteractResult.SureSuccess;
        }

        private InteractResult InteractWithRescue(DestinationPoint point)
        {
            return InteractResult.SureSuccess;
        }

        DateTime nextNPCInteractTry = DateTime.Now;
        private InteractResult InteractWithNPC(DestinationPoint npc)
        {
            var player = Memory.ObjectManager.LocalPlayer;
            double required = Math.PI / 3, now = Me.RelativeAngle(player.Rotation, npc);
            SetTurningState(now, required); // повернуться к NPC лицом

            if (Math.Abs(now) > required)
                return InteractResult.Wait;

            if (DateTime.Now > nextNPCInteractTry)
            {
                string target;
                try
                {
                    target = Memory.GetAddonMessage().Target;
                }
                catch (KeyNotFoundException)
                {
                    target = "";
                }

                if (target == npc.Name)
                {
                    Memory.KeyBoard.PressKey(KeyBindings.Interact, true);
                    return InteractResult.Success;
                }
                else
                {
                    Memory.KeyBoard.PressKey(KeyBindings.SelectNearestFriend, true);
                    nextNPCInteractTry = DateTime.Now + TimeSpan.FromMilliseconds((new Random()).Next(1200, 2400));
                    return InteractResult.Wait;
                }
            }

            return InteractResult.Wait;
        }

        private InteractResult InteractWithMailbox(DestinationPoint mailbox)
        {
            var player = Memory.ObjectManager.LocalPlayer;
            // повернуться к Mailbox, чтоб он был посреди экрана +- 5 градусов

            double required = Math.PI / 36;
            double now = Me.RelativeAngle(player.Rotation, mailbox);
            SetTurningState(now, required);

            if (Math.Abs(now) > required)
                return InteractResult.Wait;

            List<Key> zoomInKeys = new List<Key>();
            for (int i = 0; i < 20; i++)
                zoomInKeys.Add(KeyBindings.CameraZoomIn);

            Memory.KeyBoard.PressKeys(zoomInKeys, true); // приблизить камеру на максимум
            
            Thread.Sleep(2000);
            
            if (!Util.MouseCursor.NearScreenCenter())
            {
                Log("Перемещаю указатель мыши к центру экрана");
                Util.MouseCursor.MoveToScreenCenter();
                Thread.Sleep(1000);
            }

            Memory.KeyBoard.PressKey(KeyBindings.MouseInteract, true);
            Memory.KeyBoard.PressKey(KeyBindings.CameraNormal, false); // вернуть камеру в нормальное положение

            return InteractResult.Success;
        }

        DateTime? tryInteractStartTime = null;
        private InteractResult TryInteract(DestinationPoint current)
        {
            if (tryInteractStartTime == null)
                tryInteractStartTime = DateTime.Now;

            if ((DateTime.Now - (DateTime)tryInteractStartTime).TotalSeconds > 30)
            {
                Log("Не получилось сделать Interact c " + current + " в течение 30 секунд, делаю скриншот");
                Memory.KeyBoard.PressKey(KeyBindings.PrintScreen, true);
                Thread.Sleep(1000);
                return InteractResult.Failed;
            }

            else if (current.PointType == WayPointType.Simple)
                return InteractWithXYZ(current);
            else if (current.PointType == WayPointType.NPC)
                return InteractWithNPC(current);
            else if (current.PointType == WayPointType.Mailbox)
                return InteractWithMailbox(current);
            else if (current.PointType == WayPointType.Rescue)
                return InteractWithRescue(current);
            else
                throw new NotImplementedException();
        }

        TimeSpan? InteractTryInterval = null;
        DateTime NextInteractTryTime = DateTime.Now;
        /// <summary>
        /// делает повторяющиеся попытки Interact пока они не увенчаются успехом
        /// </summary>
        /// <param name="current"></param>
        private void DoInteract(DestinationPoint current)
        {
            Random rnd = new Random();

            InteractTryInterval = InteractTryInterval ?? TimeSpan.FromSeconds(rnd.Next(8, 12));

            // делаем всё это пока аддон не скажет что интеракт прошёл успешно
            string state = Memory.GetAddonMessage().CurrentState;

            if (state == current.Name || state == current.Tag)
            {
                StopNavigation();
                return;
            }

            if (DateTime.Now > NextInteractTryTime) // если мы не в паузе
            {
                InteractResult result = TryInteract(current);

                if (result == InteractResult.Wait)
                    return;

                else if (result == InteractResult.SureSuccess) // не нужно ждать проверки со стороны аддона
                {
                    StopNavigation();
                    return;
                }

                else if (result == InteractResult.Failed || result == InteractResult.Success) // готовимся к следующей попытке
                {
                    cleanupInteractTry();
                    NextInteractTryTime = DateTime.Now + (TimeSpan)InteractTryInterval;
                    InteractTryInterval = (TimeSpan)InteractTryInterval + (TimeSpan)InteractTryInterval;
                }

                else
                    throw new NotImplementedException("Unexpected InteractResult: " + result.ToString());
            }
            else
                return;
        }

        private void cleanupInteractTry()
        {
            tryInteractStartTime = null;
        }

        private void StopNavigation()
        {
            if(MovementQueue != null)
                Log("Навигатор завершает свою работу");
            MovementQueue = null;
            CurrentMovementState = false;
            CurrentTurningState = TurningState.None;
            InteractTryInterval = null;
            rememberedWaypoint = null;
            cleanupInteractTry();
            Memory.KeyBoard.KeyUpAll();
        }

        private void MakeRoute(string query)
        {
            StopNavigation();
            
            Queue<WayPoint> points;
            
            DestinationPoint start = GetNearestDestinationPoint();
            if (!start.InRange(Me))
            {
                Log("Я не нахожусь в радиусе действия ни одной из точек назначения. Поиск ближайшего маршрута...");
                points = new Queue<WayPoint>(RouteToSomeDestinationPoint());
                start = (DestinationPoint)(points.Last());
                Log("Ближайший маршрут ведёт к " + start);
            }
            else
            {
                points = new Queue<WayPoint>();
                points.Enqueue(start);
            }

            DestinationPoint destination;
            if (Destinations.ContainsKey(query)) // by name
            {
                destination = Destinations[query];
            }
            else // by tag
            {
                List<DestinationPoint> candidates = new List<DestinationPoint>();
                foreach (DestinationPoint d in Destinations.Values)
                    if (d.Tag == query && Reachable(start, d))
                        candidates.Add(d);
                if (candidates.Count == 0)
                    throw new Exception("destination not found");
                destination = candidates[(new Random()).Next(0, candidates.Count)];
            }

            IEnumerable<DestinationPoint> metaRoute = BFS(start, destination);
            DestinationPoint current = start;
            foreach (DestinationPoint next in metaRoute)
            {
                Route route = DirectRoute(current, next);
                foreach (var point in route.Points)
                    points.Enqueue(point);
                points.Enqueue(Destinations[route.To]);
                current = next;
            }
            
            MovementQueue = new Queue<WayPoint>(points);

            Log("Проложен маршрут от " + start + " до " + destination + ", " + points.Count + " точек");
        }

        private bool Reachable(DestinationPoint start, DestinationPoint finish)
        {
            try
            {
                BFS(start, finish);
                return true;
            }
            catch (ArgumentException)
            {
                return false;
            }
        }

        private IEnumerable<DestinationPoint> BFS(DestinationPoint start, DestinationPoint finish)
        {
            Dictionary<string, int> distance = new Dictionary<string, int>();
            Dictionary<string, DestinationPoint> parent =
                new Dictionary<string, DestinationPoint>();

            distance[start.Name] = 0;

            Queue<DestinationPoint> q = new Queue<DestinationPoint>();

            q.Enqueue(start);

            while (q.Count != 0 && !distance.ContainsKey(finish.Name))
            {
                DestinationPoint current = q.Dequeue();
                foreach (Route r in Destinations.RoutesFrom(current))
                {
                    DestinationPoint to = Destinations[r.To];
                    if (!distance.ContainsKey(to.Name) || distance[current.Name] + 1 < distance[to.Name])
                    {
                        distance[to.Name] = distance[current.Name] + 1;
                        parent[to.Name] = current;
                        if (!q.Contains(to))
                            q.Enqueue(to);
                    }
                }
            }

            if (distance.ContainsKey(finish.Name))
            {
                List<DestinationPoint> l = new List<DestinationPoint>();
                DestinationPoint current = finish;
                while (current != start)
                {
                    l.Insert(0, current);
                    current = parent[current.Name];
                }
                return l;
            }
            else
            {
                throw new ArgumentException("destination unreachable");
            }
        }

        private Route DirectRoute(DestinationPoint start, DestinationPoint destination)
        {
            if (start == destination)
            {
                return new Route("empty", start.Name, destination.Name);
            }

            List<Route> directRoutes = new List<Route>(
                from route in Destinations.RoutesFrom(start)
                where route.To == destination.Name
                select route);

            if (directRoutes.Count == 0)
            {
                return null;
            }
            else
            {
                Route route = directRoutes[(new Random()).Next(0, directRoutes.Count)];
                return route;
            }
        }
    }
}
