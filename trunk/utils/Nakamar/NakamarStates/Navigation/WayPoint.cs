using System;
using System.Xml.Linq;
using System.Collections.Generic;
using System.Collections;
using System.Globalization;

namespace NakamarStates
{
    /// <summary>
    /// http://www.mmowned.com/forums/c/237023-bot-developers-simple-waypoint-navigation-system-including-loading-saving.html
    /// </summary>
    public class Point
    {
        private const double SimplePointRange = 2.0;

        public float X { get; set; }
        public float Y { get; set; }
        public float Z { get; set; }

        public virtual double Range { get { return SimplePointRange; } }

        public bool InRange(double range, Point other)
        {
            return Distance(other) < range;
        }

        public virtual bool InRange(Point other)
        {
            return InRange(Range, other);
        }

        public Point(float x, float y, float z)
        {
            X = x;
            Y = y;
            Z = z;
        }

        public Point(XElement xml)
            : this(
            float.Parse(xml.Attribute("X").Value, CultureInfo.InvariantCulture),
            float.Parse(xml.Attribute("Y").Value, CultureInfo.InvariantCulture),
            float.Parse(xml.Attribute("Z").Value, CultureInfo.InvariantCulture))            
        { }

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

        public virtual XElement GetXml()
        {
            XElement xml = new XElement("Point",
                new XAttribute("X", X),
                new XAttribute("Y", Y),
                new XAttribute("Z", Z));

            return xml;
        }

        public virtual bool Equals(Point other)
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

        public override string ToString()
        {
            return "Point(" +
                "X = " + X + ", " +
                "Y = " + Y + ", " +
                "Z = " + Z + ")";
        }
    }
}
