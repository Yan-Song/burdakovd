using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Windows.Forms;

namespace Util
{
    public static class MouseCursor
    {
        const int checkAccuracy = 20;
        const int moveAccuracy = 10;
        static readonly Random generator = new Random();

        public static Point ScreenCenter
        {
            get
            {
                Rectangle bounds = Screen.PrimaryScreen.Bounds;
                return new Point(bounds.Left + bounds.Width / 2, bounds.Top + bounds.Height / 2);
            }
        }

        public static bool NearScreenCenter()
        {
            Point center = ScreenCenter;
            return
                Math.Abs(center.X - Cursor.Position.X) < checkAccuracy
                && Math.Abs(center.Y - Cursor.Position.Y) < checkAccuracy;
        }

        public static void MoveToScreenCenter()
        {
            Point position = ScreenCenter;
            position.X += generator.Next(-moveAccuracy, moveAccuracy);
            position.Y += generator.Next(-moveAccuracy, moveAccuracy);
            Cursor.Position = position;
        }
    }
}
