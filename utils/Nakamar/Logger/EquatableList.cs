using System;
using System.Collections.Generic;
using System.Linq;


namespace Util
{
    public class EquatableList<T> : List<T>, IEquatable<EquatableList<T>>
    {
        public EquatableList(params T[] p) : base(p)
        {
        }

        public EquatableList()
            : base()
        {
        }

        #region Члены IEquatable<EquatableList<T>>

        public bool Equals(EquatableList<T> other)
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
