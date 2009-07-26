using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows.Input;
using Magic;
using Util;

namespace WoWMemoryManager
{
    public class KeyBoard
    {
        #region DllImport

        /// <summary>
        /// If the function fails, the return value is zero. To get extended error information, call GetLastError.
        /// </summary>
        /// <param name="hWnd"></param>
        /// <param name="Msg"></param>
        /// <param name="wParam"></param>
        /// <param name="lParam"></param>
        /// <returns></returns>
        [return: MarshalAs(UnmanagedType.Bool)]
        [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        static extern bool PostMessage(IntPtr hWnd, UInt32 Msg, UInt32 wParam,
           UInt32 lParam);

        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        static extern short VkKeyScan(char ch);

        [DllImport("user32.dll")]
        static extern IntPtr GetForegroundWindow();

        [DllImport("user32.dll")]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool SetForegroundWindow(IntPtr hWnd);

        [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        public static extern IntPtr FindWindowEx(IntPtr hwndParent, IntPtr hwndChildAfter, string lpszClass, string lpszWindow);

        [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        public static extern IntPtr FindWindowEx(IntPtr parentHandle, IntPtr childAfter, string className, IntPtr windowTitle);

        [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        public static extern IntPtr FindWindow(string lpClassName, string lpWindowName);

        [DllImport("user32.dll", EntryPoint = "FindWindow", SetLastError = true, CharSet = CharSet.Auto)]
        public static extern IntPtr FindWindowByCaption(IntPtr ZeroOnly, string lpWindowName);

        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        static extern uint MapVirtualKey(uint uCode, uint uMapType);

        #endregion

        /// <summary>
        /// тут могут быть проблемы если окно не просто на заднем плане, а ещё и свёрнуто,
        /// то эта функция его не разворачивает, а активирует прямо свёрнутое, после чего оно ведёт себя странно
        /// </summary>
        public void CheckForeground()
        {
            if (GetForegroundWindow() != window)
            {
                SetForegroundWindow(window);
            }
        }

        private void PostMessageSafe(UInt32 msg, UInt32 wParam, UInt32 lParam)
        {
            bool returnValue = PostMessage(window, msg, wParam, lParam);
            if (!returnValue)
                throw new Win32Exception(Marshal.GetLastWin32Error());
        }

        private uint ScanCode(int k)
        {
            uint code = MapVirtualKey((uint)k, MAPVK_VK_TO_VSC);
            Debug.Assert(code < 256);
            return code;
        }

        #region const

        private const int WM_KEYDOWN = 0x100;
        private const int WM_KEYUP = 0x101;
        private const int WM_CHAR = 0x102;
        private const int WM_UNICHAR = 0x109;
        private const int WM_IME_CHAR = 0x286;

        // http://msdn.microsoft.com/en-us/library/ms646280(VS.85).aspx
        private const uint TransitionState = (uint)1 << 31;
        private const uint PreviousKeyState = (uint)1 << 30;
        private const uint KeyUp_lParam = TransitionState | PreviousKeyState | 1; // 1 is Repeat count
        private const uint KeyDown_lParam = 1;  // 1 is Repeat count
        private const uint Char_lParam = 1;
        private const int  ScanCodeOffset = 16;

        private const uint MAPVK_VK_TO_VSC = 0x00;
        private const uint MAPVK_VSC_TO_VK = 0x01;
        private const uint MAPVK_VK_TO_CHAR = 0x02;
        private const uint MAPVK_VSC_TO_VK_EX = 0x03;
        private const uint MAPVK_VK_TO_VSC_EX = 0x04;

        #endregion

        private List<int> PressedKeys = new List<int>();
        private Random rnd = new Random();
        private IntPtr window;

        public KeyBoard(IntPtr Window)
        {
            window = Window;
        }
        
        #region SendKeys

        public void KeyDown(int virtualKeyCode)
        {
            if (PressedKeys.Contains(virtualKeyCode)) return;
            PostMessageSafe(WM_KEYDOWN, (uint)virtualKeyCode, KeyDown_lParam + (ScanCode(virtualKeyCode)<<ScanCodeOffset));
            PressedKeys.Add(virtualKeyCode);
        }

        public void KeyDown(Key key)
        {
            KeyDown(KeyInterop.VirtualKeyFromKey(key));
        }

        public void KeyUp(int virtualKeyCode)
        {
            if (!PressedKeys.Contains(virtualKeyCode)) return;
            PressedKeys.Remove(virtualKeyCode);
            PostMessageSafe(WM_KEYUP, (uint)virtualKeyCode, KeyUp_lParam + (ScanCode(virtualKeyCode) << ScanCodeOffset));
        }

        public void KeyUp(Key key)
        {
            KeyUp(KeyInterop.VirtualKeyFromKey(key));
        }

        /// <summary>
        /// KeyDown and KeyUp
        /// </summary>
        /// <param name="k"></param>
        public void PressKey(Key key)
        {
            PressKey(KeyInterop.VirtualKeyFromKey(key));
        }

        public void PressKey(int virtualKeyCode)
        {
            KeyDown(virtualKeyCode);
            Thread.Sleep(rnd.Next(20, 40));
            KeyUp(virtualKeyCode);
        }

        public void SendText(char c)
        {
            PostMessageSafe(WM_CHAR, (uint)c, Char_lParam);
        }

        public void SendText(string text)
        {
            foreach (char c in text)
            {
                Thread.Sleep(rnd.Next(50, 100));
                SendText(c);
            }
        }

        #endregion
    }
}
