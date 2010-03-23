using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Xml.Linq;
using System.Xml;
using System.Collections;
using System;

namespace Plugins
{
    [Serializable]
    public class WayPointSet : Dictionary<string, DestinationPoint>
    {
        public Dictionary<string, List<Route>> Routes;

        public int RoutesCount
        {
            get
            {
                return Routes.Select(kvp => kvp.Value.Count).Sum();
            }
        }

        public WayPointSet() : base()
        {
            Routes = new Dictionary<string, List<Route>>();
        }

        public WayPointSet(string filePath)
            : this()
        {
            if (!File.Exists(filePath))
            {
                throw new FileNotFoundException("Could not find the specified file!", filePath);
            }

            XElement file = XElement.Load(filePath);

            IEnumerable<XElement> destinationPoints = file.Descendants("DestinationPoint");
            foreach (XElement destinationPoint in destinationPoints)
            {
                DestinationPoint p = new DestinationPoint(destinationPoint);
                this[p.Name] = p;
            }

            IEnumerable<XElement> routes = file.Descendants("Route");
            foreach (XElement xroute in routes)
            {
                Route route = new Route(xroute);
                Add(route);
            }
        }

        public void Save(string filePath)
        {
            XElement file = new XElement("WayPointSet");

            foreach (DestinationPoint p in this.Values)
                file.Add(p.GetXml());

            foreach (var routes in this.Routes.Values)
                foreach (Route route in routes)
                    file.Add(route.GetXml());

            file.Save(filePath);
        }

        public void Add(DestinationPoint point)
        {
            point.Name = point.Name ?? NewName();
            this[point.Name] = point;
        }

        public string NewName(string prefix, HashSet<string> names)
        {
            string name;
            int n = 1;
            do
            {
                name = prefix + n++;
            }
            while (names.Contains(name));
            return name;
        }

        public string NewName(string prefix)
        {
            return NewName(prefix, new HashSet<string>(this.Keys));
        }

        public string NewName()
        {
            return NewName("DestinationPoint");
        }

        public string NewRouteName()
        {
            HashSet<string> names = new HashSet<string>();
            foreach(var routes in Routes.Values)
                foreach(var route in routes)
                    names.Add(route.Name);

            return NewName("Маршрут", names);
        }

        public void Add(Route route)
        {
            string from = route.From;
            if(!Routes.ContainsKey(from))
                Routes[from] = new List<Route>();

            Routes[from].Add(route);
        }

        public IEnumerable<Route> RoutesFrom(DestinationPoint from)
        {
            if (Routes.ContainsKey(from.Name))
                return Routes[from.Name];
            else
                return new List<Route>();
        }
    }
}
