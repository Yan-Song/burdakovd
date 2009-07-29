using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Xml.Linq;
using System.Xml;
using System.Collections;

namespace NakamarStates
{
    public class WayPointList : Dictionary<string, Point>
    {
        public WayPointList() : base() { }

        public WayPointList(string filePath)
            : this()
        {
            if (!File.Exists(filePath))
            {
                throw new FileNotFoundException("Could not find the specified file!", filePath);
            }

            XElement file = XElement.Load(filePath);
            IEnumerable<XElement> points = file.Descendants("Point");
            foreach (XElement point in points)
            {
                Point p = new Point(point);
                this[p.Name] = p;
            }
        }

        public void Save(string filePath)
        {
            XElement file = new XElement("WayPointList");

            foreach (Point p in this.Values)
                file.Add(p.GetXml());

            file.Save(filePath);
        }

        public void Add(Point point)
        {
            if (point.Name == null)
            {
                int n = 1;
                do
                {
                    point.Name = "WayPoint" + n++;
                }
                while (this.ContainsKey(point.Name));
            }
            this[point.Name] = point;
        }
    }
}
