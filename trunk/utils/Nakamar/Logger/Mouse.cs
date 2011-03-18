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
        #region WinAPI

        [StructLayout(LayoutKind.Sequential)]
        private struct RECT
        {
            public int Left;        // x position of upper-left corner
            public int Top;         // y position of upper-left corner
            public int Right;       // x position of lower-right corner
            public int Bottom;      // y position of lower-right corner
        }

        [DllImport("user32.dll")]
        [return: MarshalAs(UnmanagedType.Bool)]
        private static extern bool GetWindowRect(IntPtr hWnd, out RECT lpRect);

        #endregion

        #region Static and Const fields

        private const int checkAccuracy = 5;
        private const int moveAccuracy = 3;
        private static readonly Random generator = new Random();

        #endregion

        #region Screen/Window bounds

        public static System.Drawing.Point ScreenCenter()
        {
            Rectangle bounds = Screen.PrimaryScreen.Bounds;
            return new System.Drawing.Point(bounds.Left + bounds.Width / 2, bounds.Top + bounds.Height / 2);
        }

        public static System.Drawing.Point WindowCenter(IntPtr window)
        {
            RECT bounds;
            if (GetWindowRect(window, out bounds))
            {
                return new System.Drawing.Point((bounds.Left + bounds.Right) / 2, (bounds.Top + bounds.Bottom) / 2);
            }
            else
            {
                Logger.LogError("Mouse", "Не удалось получить координаты окна WoW: GetWindowRect failed");
                throw new ApplicationException("Не удалось получить координаты окна WoW: GetWindowRect failed");
            }
            
        }

        #endregion

        #region Position tests

        public static bool NearPoint(System.Drawing.Point point)
        {
            return
                Math.Abs(point.X - Cursor.Position.X) < checkAccuracy
                && Math.Abs(point.Y - Cursor.Position.Y) < checkAccuracy;
        }

        public static bool NearScreenCenter()
        {
            return NearPoint(ScreenCenter());
        }

        public static bool NearWindowCenter(IntPtr window)
        {
            return NearPoint(WindowCenter(window));
        }

        #endregion

        #region Movement

        public static void moveTo(System.Drawing.Point position)
        {
            position.X += generator.Next(-moveAccuracy, moveAccuracy);
            position.Y += generator.Next(-moveAccuracy, moveAccuracy);
            Cursor.Position = position;
        }

        public static void MoveToWindowCenter(IntPtr window)
        {
            moveTo(WindowCenter(window));
        }

        public static void MoveToScreenCenter()
        {
            moveTo(ScreenCenter());
        }

        #endregion
    }
}
