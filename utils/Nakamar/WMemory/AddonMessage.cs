using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WoWMemoryManager
{
    public class AddonMessage
    {
        public int Id;
        public string Command;
        public string[] Arguments;
        public string Target;
        public string DoNotRestart;
        public bool NeedPurchaseConfirmation;
        public string CurrentState;
        public bool NothingToDo;
        public GuildBankInfo guildBank;

        public override string ToString()
        {
            return "[AddonMessage #" + Id + "]: " + Command + "(" + string.Join(", ", Arguments) + ")";
        }
        /// <summary>
        /// возвращает null если такого аргумента нет
        /// </summary>
        /// <param name="position"></param>
        /// <returns></returns>
        public string Argument(int position)
        {
            return Arguments.ElementAtOrDefault(position);
        }

        /// <summary>
        /// возвращает defaultValue если такого аргумента нет
        /// </summary>
        /// <param name="position"></param>
        /// <param name="defaultValue"></param>
        /// <returns></returns>
        public string Argument(int position, string defaultValue)
        {
            return Argument(position) ?? defaultValue;
        }
    }
}
