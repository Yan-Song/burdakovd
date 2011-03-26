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
                if (message != null && message.lastGuildBankCheckTime > lastReportTime)
                {
                    lastReportTime = message.lastGuildBankCheckTime;

                    string target = Machine.settings["goldReports"];
                    if (target.StartsWith("http"))
                    {
                        string url = target
                            .Replace("%SERVER%", HttpUtility.UrlEncode(message.lastGuildBankCheckServer))
                            .Replace("%FACTION%", HttpUtility.UrlEncode(message.lastGuildBankCheckFaction))
                            .Replace("%COPPERS%", message.guildBalance.ToString());

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
                            .Replace("%SERVER%", message.lastGuildBankCheckServer)
                            .Replace("%FACTION%", message.lastGuildBankCheckFaction);

                        string content = message.guildBalance.ToString();

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
