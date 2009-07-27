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

        public static void Log(string prefix, string message)
        {
            RawLog("[" + DateTime.Now.ToLongTimeString() + "] [" + prefix + "] " + message);
        }

        public static void LogError(string prefix, string message)
        {
            Log(prefix, "Ошибка: " + message);
        }

        /// <summary>
        /// функция записывает в лог изменения value, относительно предыдущего с тем же key
        /// </summary>
        /// <param name="key"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        public static void Watch(string prefix, string key, object ovalue)
        {
            string value = ovalue == null ? "null" : ovalue.ToString();

            lock(CurrentValues)
            {
                if (!CurrentValues.ContainsKey(key) || CurrentValues[key] != value)
                {
                    CurrentValues[key] = value;
                    Log(prefix, key + " = " + value);
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
