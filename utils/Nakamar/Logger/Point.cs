using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Util
{
    /// <summary>
    /// поддерживает разные геометрические операции
    /// </summary>
    public class Point
    {
        public double X { get; set; }
        public double Y { get; set; }
        public double Z { get; set; }

        public Point(double x, double y, double z)
        {
            X = x;
            Y = y;
            Z = z;
        }

        public double Distance(Point to)
        {
            return Distance(to.X, to.Y, to.Z);
        }

        public double Distance2D(Point to)
        {
            return Distance(to.X, to.Y, this.Z);
        }

        public double Distance(double toX, double toY, double toZ)
        {
            double dX = X - toX;
            double dY = Y - toY;
            double dZ = Z - toZ;
            return Math.Sqrt(dX * dX + dY * dY + dZ * dZ);
        }

        public static Point operator -(Point first, Point second)
        {
            return new Point(first.X - second.X, first.Y - second.Y, first.Z - second.Z);
        }

        public static Point operator +(Point first, Point second)
        {
            return new Point(first.X + second.X, first.Y + second.Y, first.Z + second.Z);
        }

        public static double operator *(Point first, Point second)
        {
            return first.X * second.X + first.Y * second.Y + first.Z * second.Z;
        }

        public static Point operator *(double k, Point p)
        {
            return new Point(k * p.X, k * p.Y, k * p.Z);
        }

        /// <summary>
        /// расстояние до заданного отрезка
        /// http://algolist.manual.ru/maths/geom/distance/pointline.php
        /// </summary>
        /// <param name="P0"></param>
        /// <param name="?"></param>
        /// <returns></returns>
        public double Distance(Point p0, Point p1)
        {
            Point v = p1 - p0;
            Point w = this - p0;
            double c1, c2;
            if ((c1 = w * v) <= 0)
                return Distance(p0);
            if ((c2 = v * v) <= c1)
                return Distance(p1);
            double b = c1 / c2;
            Point pb = p0 + b * v;
            return Distance(pb);
        }
        public virtual bool Equals(Point other)
        {
            return other != null && other.X == X && other.Y == Y && other.Z == Z;
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
            return !(left == right);
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
