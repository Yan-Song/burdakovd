using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Xml.Linq;
using System.Xml;
using System.Collections;

namespace NakamarStates
{
    public class WayPointSet : Dictionary<string, DestinationPoint>
    {
        public Dictionary<string, List<Route>> Routes;

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
                string from = route.From;
                if(!Routes.ContainsKey(from))
                    Routes[from] = new List<Route>();
                Routes[from].Add(route);
            }
        }

        public void Save(string filePath)
        {
            XElement file = new XElement("WayPointSet");

            foreach (DestinationPoint p in this.Values)
                file.Add(p.GetXml());

            foreach (var kvp in this.Routes)
                foreach (Route route in kvp.Value)
                    file.Add(route.GetXml());

            file.Save(filePath);
        }

        public void Add(DestinationPoint point)
        {
            point.Name = point.Name ?? NewName();
            this[point.Name] = point;
        }

        public string NewName()
        {
            string name;
            int n = 1;
            do
            {
                name = "DestinationPoint" + n++;
            }
            while (this.ContainsKey(name));
            return name;
        }
    }
}
