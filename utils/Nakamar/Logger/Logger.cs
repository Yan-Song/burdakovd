using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Util
{
    public static class Logger
    {
        private static Dictionary<string,string> CurrentValues = new Dictionary<string,string>();

        public delegate void LogFunction(string message);

        public static LogFunction RawLog = new LogFunction(System.Console.WriteLine);

        public static LogFunction Log = delegate(string message)
        {
            RawLog("[" + DateTime.Now.ToLongTimeString() + "] " + message);
        };

        public static LogFunction LogError = delegate(string message)
        {
            Log("Ошибка: " + message);
        };

        /// <summary>
        /// функция записывает в лог изменения value, относительно предыдущего с тем же key
        /// </summary>
        /// <param name="key"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        public static void Watch(string key, string value)
        {
            lock(CurrentValues)
            {
                if (!CurrentValues.ContainsKey(key) || CurrentValues[key] != value)
                {
                    CurrentValues[key] = value;
                    Logger.Log(key + " = " + value);
                }
            }
        }

        public static void ClearValues()
        {
            lock (CurrentValues)
            {
                CurrentValues.Clear();
            }
        }
    }
}
