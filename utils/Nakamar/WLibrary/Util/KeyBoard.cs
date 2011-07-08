using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows.Input;

namespace WLibrary
{
    public class KeyBoard
    {
        private void PostOrSendMessageSafe(UInt32 msg, UInt32 wParam, UInt32 lParam, bool wait)
        {
            if (wait)
                Extern.SendMessage(window, msg, wParam, lParam);
            else
            {
                bool returnValue = Extern.PostMessage(window, msg, wParam, lParam);
                if (!returnValue)
                    throw new Win32Exception(Marshal.GetLastWin32Error());
            }
        }

        private uint ScanCode(int k)
        {
            uint code = Extern.MapVirtualKey((uint)k, MAPVK_VK_TO_VSC);
            Debug.Assert(code < 256);
            Debug.Assert(code >= 0);
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

        public void KeyDown(int virtualKeyCode, bool wait)
        {
            if (PressedKeys.Contains(virtualKeyCode)) return;
            PostOrSendMessageSafe(WM_KEYDOWN, (uint)virtualKeyCode, KeyDown_lParam + (ScanCode(virtualKeyCode)<<ScanCodeOffset), wait);
            PressedKeys.Add(virtualKeyCode);
        }

        public void KeyDown(Key key, bool wait)
        {
            KeyDown(KeyInterop.VirtualKeyFromKey(key), wait);
        }

        public void KeyUp(int virtualKeyCode, bool wait)
        {
            if (!PressedKeys.Contains(virtualKeyCode)) return;
            PressedKeys.Remove(virtualKeyCode);
            PostOrSendMessageSafe(WM_KEYUP, (uint)virtualKeyCode, KeyUp_lParam + (ScanCode(virtualKeyCode) << ScanCodeOffset), wait);
        }

        public void KeyUp(Key key, bool wait)
        {
            KeyUp(KeyInterop.VirtualKeyFromKey(key), wait);
        }

        /// <summary>
        /// KeyDown and KeyUp
        /// </summary>
        /// <param name="k"></param>
        public void PressKey(Key key, bool wait)
        {
            PressKey(KeyInterop.VirtualKeyFromKey(key), wait);
        }

        public void PressKey(int virtualKeyCode, bool wait)
        {
            KeyDown(virtualKeyCode, wait);
            Thread.Sleep(rnd.Next(20, 40));
            KeyUp(virtualKeyCode, wait);
        }

        public void SendText(char c, bool wait)
        {
            PostOrSendMessageSafe(WM_CHAR, (uint)c, Char_lParam, wait);
        }

        public void SendText(string text, bool wait)
        {
            foreach (char c in text)
            {
                Thread.Sleep(rnd.Next(100, 200));
                SendText(c, wait);
            }
        }

        public void KeyUpAll()
        {
            List<int> p = new List<int>(PressedKeys);
            foreach(int key in p)
                KeyUp(key, false);
        }

        public void PressKeys(IEnumerable<Key> keys, bool wait)
        {
            foreach (Key key in keys)
            {
                Thread.Sleep(rnd.Next(50, 100));
                PressKey(key, wait);
            }
        }

        #endregion
    }
}
