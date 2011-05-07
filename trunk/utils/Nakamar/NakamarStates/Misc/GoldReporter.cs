using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using FiniteStateMachine;
using WoWMemoryManager;
using System.IO;
using System.Web;

namespace Plugins
{
    public class GoldReporter : State
    {
        private long lastReportTime = 0;

        public GoldReporter(object machine, object memory) : base(machine, memory) { }

        public override int Priority
        {
            get { return 50000; }
        }

        public override bool NeedToRun
        {
            get
            {
                AddonMessage message = Memory.GetAddonMessage();
                if (message != null && message.guildBank != null && message.guildBank.checkTime > lastReportTime)
                {
                    lastReportTime = message.guildBank.checkTime;

                    string target = Machine.settings["goldReports"];
                    if (target.StartsWith("http"))
                    {
                        string url = target
                            .Replace("%SERVER%", HttpUtility.UrlEncode(message.guildBank.server))
                            .Replace("%FACTION%", HttpUtility.UrlEncode(message.guildBank.faction))
                            .Replace("%PLAYERNAME%", HttpUtility.UrlEncode(message.guildBank.playerName))
                            .Replace("%COPPERS%", message.guildBank.balance.ToString())
                            .Replace("%DELTA%", message.guildBank.delta.ToString());

                        Log(String.Format("GET {0}", url));

                        try
                        {
                            HttpWebRequest request = (HttpWebRequest)WebRequest.Create(url);
                            HttpWebResponse response = (HttpWebResponse)request.GetResponse();
                            Log("HTTP response status: " + response.StatusCode);
                        }
                        catch (WebException e)
                        {
                            LogError(e.ToString());
                        }

                        
                    }
                    else
                    {
                        string filename = target
                            .Replace("%SERVER%", message.guildBank.server)
                            .Replace("%FACTION%", message.guildBank.faction)
                            .Replace("%PLAYERNAME%", message.guildBank.playerName);

                        string content = message.guildBank.balance.ToString() + ", " + message.guildBank.delta.ToString();

                        Log(String.Format("Записываю {0} в {1}", content, filename));
                        File.WriteAllText(filename, content);
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
