using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Util;

namespace Nakamar
{
    public abstract class Loader
    {
        protected Loader() { }

        protected void Log(string message)
        {
            Logger.Log(this.GetType().Name, message);
        }

        protected void LogError(string message)
        {
            Logger.LogError(this.GetType().Name, message);
        }

        /// <summary>
        /// возвращает null, если ничего не препятствует запуску WoW, иначе причину
        /// </summary>
        /// <returns></returns>
        public abstract string WhyShouldNotStartWoW();

        public abstract void PrepareForStartWoW();
    }
}
