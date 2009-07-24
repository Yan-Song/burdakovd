// 
// Copyright © ApocDev 2009 <apoc@apocdev.com>
//
using System;
using System.Collections.Generic;
using WoWMemoryManager;

namespace FiniteStateMachine
{
    public abstract class State : IComparable<State>, IComparer<State>
    {
        protected Engine Machine;
        protected MemoryManager Memory;

        protected State() { }

        protected State(object machine, object memory)
        {
            Machine = machine as Engine;
            Memory = memory as MemoryManager;
        }

        public abstract int Priority { get; }

        public abstract bool NeedToRun { get; }

        /// <summary>
        /// Determines the frequency (Frame count) between each attempt
        /// to check, and run, this state.
        /// </summary>
        public virtual int Frequency { get { return 1; } }

        #region IComparable<State> Members

        public int CompareTo(State other)
        {
            // We want the highest first.
            // int, by default, chooses the lowest to be sorted
            // at the bottom of the list. We want the opposite.
            return -Priority.CompareTo(other.Priority);
        }

        #endregion

        #region IComparer<State> Members

        public int Compare(State x, State y)
        {
            return -x.Priority.CompareTo(y.Priority);
        }

        #endregion

        public abstract void Run();
    }
}
