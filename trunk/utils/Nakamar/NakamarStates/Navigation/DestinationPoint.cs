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
    }

    public class DestinationPoint : Point
    {
        private const double
            NPCRange = 3.0,
            MailboxRange = 3.0,
            XYZRange = 1.0;

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
                return XYZRange;
            }
        }

        public DestinationPoint(string name, WayPointType type, string tag, float x, float y, float z) : base(x, y, z)
        {
            Type = type;
            Name = name;
            Tag = tag;
        }

        public DestinationPoint(string name, WayPointType type, float x, float y, float z)
            : this
                (name, type, "", x, y, z) { }

        public DestinationPoint(WayPointType type, float x, float y, float z) : this(null, type, x, y, z) {}

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
            return "DestinationPoint(Type=" + Type + ", " +
                "Name = " + Name + ", " +
                "Tag = " + Tag + ", " +
                "X = " + X + ", " +
                "Y = " + Y + ", " +
                "Z = " + Z + ")";
        }
    }
}
