using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace Plugins.AccountManager
{
    [Serializable]
    public class Session
    {
        public DateTime Start;
        public DateTime End;

        public Session()
        {
            Start = DateTime.Now;
            End = DateTime.Now;
        }

        public void Update()
        {
            End = DateTime.Now;
        }

        public TimeSpan Length()
        {
            return End - Start;
        }

        public TimeSpan LengthAfter(DateTime limit)
        {
            if (limit > End)
            {
                return TimeSpan.Zero;
            }
            else
            {
                return End - (limit > Start ? limit : Start);
            }
        }
    }

    [Serializable]
    public class Profile
    {
        public string AccountName;
        public string Password;
        public string Realm;
        public bool Enabled = true;

        public List<Session> Sessions = new List<Session>();

        public List<DateTime> NothingToDoTimes = new List<DateTime>();

        public void AddSession()
        {
            Sessions.Add(new Session());
        }

        public void UpdateSession()
        {
            Sessions.Last().Update();
        }

        public void NothingToDo()
        {
            NothingToDoTimes.Add(DateTime.Now);
        }

        public TimeSpan SinceLastNothingToDo()
        {
            if(NothingToDoTimes.Count > 0)
            {
                return DateTime.Now - NothingToDoTimes.Last();
            }
            else
            {
                return TimeSpan.MaxValue;
            }
        }

        public double BottedLast24Hours()
        {
            return Sessions.Select(session => session.LengthAfter(DateTime.Now - TimeSpan.FromHours(24)).TotalHours).Sum();
        }
    }
}
