using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Nakamar
{
    static class Logger
    {
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

    }
}
