using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Diagnostics;

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

        [DllImport("user32.dll")]
        private static extern bool GetWindowRect(IntPtr hWnd, out Rectangle rect);

        public static Point WindowCenter(IntPtr window)
        {
            Rectangle bounds = new Rectangle();
            Debug.Assert(GetWindowRect(window, out bounds)); // часто не работает
            // Это не настоящий прямоугольник, и вместо width && height там right && bottom
            return new Point((bounds.Left + bounds.Width) / 2, (bounds.Top + bounds.Height) / 2);
        }

        public static bool NearCenter(Point center)
        {
            return
                Math.Abs(center.X - Cursor.Position.X) < checkAccuracy
                && Math.Abs(center.Y - Cursor.Position.Y) < checkAccuracy;
        }

        public static bool NearScreenCenter()
        {
            return NearCenter(ScreenCenter);
        }

        public static bool NearWindowCenter(IntPtr window)
        {
            return NearCenter(WindowCenter(window));
        }

        public static void MoveToWindowCenter(IntPtr window)
        {
            Point position = WindowCenter(window);
            position.X += generator.Next(-moveAccuracy, moveAccuracy);
            position.Y += generator.Next(-moveAccuracy, moveAccuracy);
            Cursor.Position = position;
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
