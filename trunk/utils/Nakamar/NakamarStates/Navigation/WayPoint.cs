using System;
using System.Xml.Linq;
using System.Collections.Generic;
using System.Collections;
using System.Globalization;

namespace NakamarStates
{
    public enum WayPointType
    {
        Simple,
        NPC,
        Mailbox,
    }
    /// <summary>
    /// http://www.mmowned.com/forums/c/237023-bot-developers-simple-waypoint-navigation-system-including-loading-saving.html
    /// </summary>
    public class Point
    {
        public float X { get; set; }
        public float Y { get; set; }
        public float Z { get; set; }
        public WayPointType Type { get; private set; }
        public string Name { get; set; }
        public string Tag { get; set; }
        /// <summary>
        /// names of WayPoints, directly reachable from this
        /// </summary>
        public List<string> Neighbours { get; private set;  }

        public Point(string name, WayPointType type, string tag, float x, float y, float z)
        {
            X = x;
            Y = y;
            Z = z;
            Type = type;
            Name = name;
            Tag = tag;
            Neighbours = new List<string>();
        }

        public Point(string name, WayPointType type, float x, float y, float z)
            : this
                (name, type, "", x, y, z) { }

        public Point(WayPointType type, float x, float y, float z) : this(null, type, x, y, z) {}

        public Point(float x, float y, float z) : this(WayPointType.Simple, x, y, z) {}

        public Point(XElement xml)
            : this(xml.Attribute("Name").Value,
            (WayPointType)Enum.Parse(typeof(WayPointType), xml.Attribute("Type").Value),
            xml.Attribute("Tag").Value,
            float.Parse(xml.Attribute("X").Value, CultureInfo.InvariantCulture),
            float.Parse(xml.Attribute("Y").Value, CultureInfo.InvariantCulture),
            float.Parse(xml.Attribute("Z").Value, CultureInfo.InvariantCulture))
            
        {
            IEnumerable<XElement> neighbours = xml.Descendants("Neighbour");
            foreach (XElement neighbour in neighbours)
                Neighbours.Add(neighbour.Attribute("Name").Value);
        }

        public double Distance(Point to)
        {
            return Distance(to.X, to.Y, to.Z);
        }

        public double Distance(float toX, float toY, float toZ)
        {
            float dX = X - toX;
            float dY = Y - toY;
            float dZ = Z - toZ;
            return Math.Sqrt(dX * dX + dY * dY + dZ * dZ);
        }

        public XElement GetXml()
        {
            XElement xml = new XElement("Point",
                new XAttribute("Name", Name),
                new XAttribute("Type", Type),
                new XAttribute("Tag", Tag),
                new XAttribute("X", X),
                new XAttribute("Y", Y),
                new XAttribute("Z", Z));

            foreach (string neighbour in Neighbours)
                xml.Add(new XElement("Neighbour", new XAttribute("Name", neighbour)));

            return xml;
        }

        public bool Equals(Point other)
        {
            return other!=null && other.X == X && other.Y == Y && other.Z == Z;
        }

        public override bool Equals(object obj)
        {
            if (ReferenceEquals(null, obj))
            {
                return false;
            }
            if (obj.GetType() != typeof(Point))
            {
                return false;
            }
            return Equals((Point)obj);
        }

        public override int GetHashCode()
        {
            unchecked
            {
                int result = X.GetHashCode();
                result = (result * 397) ^ Y.GetHashCode();
                result = (result * 397) ^ Z.GetHashCode();
                return result;
            }
        }

        public static bool operator ==(Point left, Point right)
        {
            return ReferenceEquals(left, null) ? ReferenceEquals(right, null) : left.Equals(right);
        }

        public static bool operator !=(Point left, Point right)
        {
            return !(left==right);
        }

        public void AddNeighbour(string neighbour)
        {
            if (!Neighbours.Contains(neighbour))
                Neighbours.Add(neighbour);
        }

        public void AddNeighbour(Point neighbour)
        {
            AddNeighbour(neighbour.Name);
        }

        public void RemoveNeighbour(string neighbour)
        {
            if (Neighbours.Contains(neighbour))
                Neighbours.Remove(neighbour);
        }

        public void RemoveNeighbour(Point neighbour)
        {
            RemoveNeighbour(neighbour.Name);
        }

        public override string ToString()
        {
            return "WayPoint(Type=" + Type + ", " +
                "Name = " + Name + ", " +
                "Tag = " + Tag + ", " +
                "X = " + X + ", " +
                "Y = " + Y + ", " +
                "Z = " + Z + ")";
        }
    }
}
