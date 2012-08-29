using System;
using System.Collections.Generic;

namespace Util
{
    public static class Logger
    {
        private static Dictionary<string,string> CurrentValues = new Dictionary<string,string>();

        public delegate void LogFunction(string message);

        public static LogFunction RawLog = new LogFunction(System.Console.WriteLine);

        private static void Log(string tag, string type, string message)
        {
            string prefix = string.Format("[{0}][{1}][{2}]",
                                          DateTime.Now.ToLongTimeString(),
                                          type,
                                          tag);
            string[] lines = message.Split(new string[] { Environment.NewLine },
                                           StringSplitOptions.None);
            bool prefixWritten = false;
            foreach(string line in lines)
            {
                RawLog(string.Format("{0} {1}",
                                     prefixWritten ?
                                        new string(' ', prefix.Length) :
                                        prefix,
                                     line));
                prefixWritten = true;
            }
        }

        public static void Log(string tag, string message)
        {
            Log(tag, "I", message);
        }

        public static void LogError(string tag, string message)
        {
            Log(tag, "E", message);
        }

        /// <summary>
        /// функция записывает в лог изменения value, относительно предыдущего с тем же key
        /// </summary>
        /// <param name="key"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        public static void Watch(string tag, string key, object ovalue)
        {
            string value = ovalue == null ? "null" : ovalue.ToString();

            lock(CurrentValues)
            {
                if (!CurrentValues.ContainsKey(key) || CurrentValues[key] != value)
                {
                    CurrentValues[key] = value;
                    Log(tag, key + " = " + value);
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
