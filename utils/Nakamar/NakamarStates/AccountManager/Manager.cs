using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Plugins.Properties;

namespace Plugins.AccountManager
{
    class Manager
    {
        /// <summary>
        /// возвращает наиболее подходящий для боттинга профиль, или же null, если ни один не найден
        /// </summary>
        public static string GetBestProfile()
        {
            var good = Settings.Default.Profiles
                .Where(kvp =>
                    kvp.Value.Enabled &&
                    kvp.Value.BottedLast24Hours() < (double)Settings.Default.HowMuchHoursAllowedToBotEvery24Hours
                    );

            if (good.Count() == 0)
            {
                return null;
            }
            else
            {
                return good.OrderByDescending(kvp => kvp.Value.SinceLastNothingToDo()).First().Key;
            }
        }
    }
}
