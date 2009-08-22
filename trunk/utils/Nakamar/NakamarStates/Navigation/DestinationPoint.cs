using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Linq;

namespace NakamarStates
{
    public enum WayPointType
    {
        Simple,
        NPC,
        Mailbox,
        Rescue
    }

    public class DestinationPoint : WayPoint
    {
        private const double
            NPCRange = 5,
            MailboxRange = 2,
            XYZRange = 3,
            RescueRange = 10;

        public WayPointType Type { get; private set; }
        public string Name { get; set; }
        public string Tag { get; set; }

        public override double Range
        {
            get
            {
                if (Type == WayPointType.Mailbox)
                    return MailboxRange;
                if (Type == WayPointType.NPC)
                    return NPCRange;
                if (Type == WayPointType.Simple)
                    return XYZRange;
                if (Type == WayPointType.Rescue)
                    return RescueRange;
                throw new NotImplementedException(Type.ToString());
            }
        }

        public DestinationPoint(string name, WayPointType type, string tag, double x, double y, double z) : base(x, y, z)
        {
            Type = type;
            Name = name;
            Tag = tag;
        }

        public DestinationPoint(string name, WayPointType type, double x, double y, double z)
            : this
                (name, type, "", x, y, z) { }

        public DestinationPoint(WayPointType type, double x, double y, double z) : this(null, type, x, y, z) {}

        public DestinationPoint(XElement xml) : base(xml)
        {
            this.Type = (WayPointType)Enum.Parse(typeof(WayPointType), xml.Attribute("Type").Value);
            this.Name = xml.Attribute("Name").Value;
            this.Tag = xml.Attribute("Tag").Value;
        }

        public override XElement GetXml()
        {
            XElement xml = new XElement("DestinationPoint",
                new XAttribute("Name", Name),
                new XAttribute("Type", Type),
                new XAttribute("Tag", Tag),
                new XAttribute("X", X),
                new XAttribute("Y", Y),
                new XAttribute("Z", Z));

            return xml;
        }

        public virtual bool Equals(DestinationPoint other)
        {
            return other != null && other.X == X && other.Y == Y && other.Z == Z &&
                other.Name == Name && other.Type == Type && other.Tag == Tag;
        }

        public override bool Equals(object obj)
        {
            if (ReferenceEquals(null, obj))
            {
                return false;
            }
            if (obj.GetType() != typeof(DestinationPoint))
            {
                return false;
            }
            return Equals((DestinationPoint)obj);
        }

        public override int GetHashCode()
        {
            unchecked
            {
                int result = X.GetHashCode();
                result = (result * 397) ^ Y.GetHashCode();
                result = (result * 397) ^ Z.GetHashCode();
                result = (result * 397) ^ Name.GetHashCode();
                result = (result * 397) ^ Type.GetHashCode();
                result = (result * 397) ^ Tag.GetHashCode();
                return result;
            }
        }

        public override string ToString()
        {
            return "[" + Tag + "] " + Name;
        }
    }
}
