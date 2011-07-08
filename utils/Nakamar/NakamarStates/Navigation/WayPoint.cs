using System;
using System.Xml.Linq;
using System.Collections.Generic;
using System.Collections;
using System.Globalization;
using System.Windows;
using WLibrary;

namespace Plugins
{
    /// <summary>
    /// http://www.mmowned.com/forums/c/237023-bot-developers-simple-waypoint-navigation-system-including-loading-saving.html
    /// </summary>
    public class WayPoint : WLibrary.Point
    {
        private const double WayPointRange = 2.0;

        public virtual double Range { get { return WayPointRange; } }

        public bool InRange(double range, WLibrary.Point other)
        {
            return Distance(other) < range;
        }

        public virtual bool InRange(WLibrary.Point other)
        {
            return InRange(Range, other);
        }

        public virtual bool InRange2D(WLibrary.Point other)
        {
            return InRange2D(Range, other);
        }

        private bool InRange2D(double range, WLibrary.Point other)
        {
            return Distance2D(other) < range;
        }

        public WayPoint(double x, double y, double z) : base(x, y, z)
        {
        }

        public WayPoint(XElement xml)
            : this(
            double.Parse(xml.Attribute("X").Value, CultureInfo.InvariantCulture),
            double.Parse(xml.Attribute("Y").Value, CultureInfo.InvariantCulture),
            double.Parse(xml.Attribute("Z").Value, CultureInfo.InvariantCulture))            
        { }

        public virtual XElement GetXml()
        {
            XElement xml = new XElement("Point",
                new XAttribute("X", X),
                new XAttribute("Y", Y),
                new XAttribute("Z", Z));

            return xml;
        }
    }
}
