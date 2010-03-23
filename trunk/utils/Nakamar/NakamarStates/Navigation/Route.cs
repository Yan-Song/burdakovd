using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Linq;

namespace Plugins
{
    public class Route
    {
        public string From;
        public string To;
        public string Name;
        public List<WayPoint> Points;

        public Route(string name, string from, string to)
        {
            Points = new List<WayPoint>();
            Name = name;
            From = from;
            To = to;
        }

        public Route(string name)
            : this(name, null, null)
        {
        }

        public Route()
        {
        }

        public Route(XElement xml) : this(
            xml.Attribute("Name").Value,
            xml.Attribute("From").Value,
            xml.Attribute("To").Value)
        {
            foreach (XElement xpoint in xml.Descendants("Point"))
                Points.Add(new WayPoint(xpoint));
        }

        public XElement GetXml()
        {
            XElement xroute = new XElement("Route",
                new XAttribute("Name", Name),
                new XAttribute("From", From),
                new XAttribute("To", To));

            foreach (WayPoint point in Points)
                xroute.Add(point.GetXml());

            return xroute;
        }

        public double TotalLength(WayPointSet w)
        {
            double ans = 0;
            WayPoint prev = w[From];
            foreach (WayPoint p in Points)
            {
                ans += prev.Distance(p);
                prev = p;
            }
            ans += prev.Distance(w[To]);

            return ans;

        }
    }
}
