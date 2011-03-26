using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FiniteStateMachine;
using WoWMemoryManager;
using Util;
using WoWMemoryManager.WoWObject;
using System.Collections;


namespace Plugins
{
    public class Watcher : State
    {
        private const bool Enabled = true;
        private Dictionary<string,string> current = new Dictionary<string,string>();

        public Watcher(object machine, object memory) : base(machine, memory) { }

        public override int Priority
        {
            get { return 50000; }
        }

        private void Watch(string key, object value)
        {
            Logger.Watch("Watcher", key, value);
        }

        public override bool NeedToRun
        {
            get
            {
                if (Enabled)
                {
                    AddonMessage message = Memory.GetAddonMessage();
                    if (message != null)
                    {
                        Watch("addon.command", message.Command);
                        Watch("addon.needConfirmation", message.NeedPurchaseConfirmation);
                        Watch("addon.state", message.CurrentState);
                        Watch("addon.nothingToDo", message.NothingToDo);
                        Watch("addon.target", message.Target);
                        Watch("addon.guildInfo",
                            String.Format("\"{0}\" / \"{1}\" / {2} / {3} coppers",
                            message.lastGuildBankCheckServer,
                            message.lastGuildBankCheckFaction,
                            new DateTime(1970, 1, 1, 0, 0, 0, 0).AddSeconds(message.lastGuildBankCheckTime).ToLocalTime(),
                            message.guildBalance));
                    }
                }
                return false;
            }
        }

        public override void Run()
        {
            
        }
    }
}
