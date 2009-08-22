using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
using System.Xml.Linq;


namespace Util
{
    public class ComparableListOfDouble : List<double>, IEquatable<ComparableListOfDouble>
    {
        public ComparableListOfDouble(params double[] p) : base(p)
        {
        }

        public ComparableListOfDouble()
            : base()
        {
        }

        #region Члены IEquatable<ComparableArrayOfDouble>

        public bool Equals(ComparableListOfDouble other)
        {
            return this.SequenceEqual(other);
        }

        #endregion

        public override int GetHashCode()
        {
            return string.Join("|", this.Select(x => x.ToString()).ToArray()).GetHashCode();
        }
    }
}
