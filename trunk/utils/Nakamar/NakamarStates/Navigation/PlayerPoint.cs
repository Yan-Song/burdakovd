using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Numeric;
using System.Diagnostics;

namespace Plugins
{
    public class PlayerPoint : Util.Point
    {
        static readonly Vector OX = new Vector(1, 0);

        public PlayerPoint(float x, float y, float z)
            : base(x, y, z)
        {

        }

        /// <summary>
        /// угол между осью OX и проекцией вектора от this к p на плоскость XY,
        /// </summary>
        /// <param name="p"></param>
        /// <returns>0..2*Math.PI</returns>
        public double Angle(Util.Point p)
        {
            Vector v = new Vector(p.X - this.X, p.Y - this.Y);
            double angle = Vector.AngleBetween(OX, v);
            angle = angle * Math.PI / 180;
            if (angle < 0)
                angle += 2 * Math.PI;
            Debug.Assert(angle >= 0);
            Debug.Assert(angle <= 2 * Math.PI);
            return angle;
        }

        /// <summary>
        /// угол между текущим направлением и Angle
        /// </summary>
        /// <param name="p"></param>
        /// <returns>-Math.PI..Math.PI</returns>
        public double RelativeAngle(double currentRotation, WayPoint p)
        {
            double rel = Angle(p) - currentRotation;
            while (rel > Math.PI)
                rel -= 2 * Math.PI;
            while (rel < -Math.PI)
                rel += 2 * Math.PI;
            Debug.Assert(rel <= Math.PI);
            Debug.Assert(rel >= -Math.PI);
            return rel;
        }
    }
}
