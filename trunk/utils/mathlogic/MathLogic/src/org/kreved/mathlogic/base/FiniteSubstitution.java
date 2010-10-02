package org.kreved.mathlogic.base;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;

import org.kreved.mathlogic.util.Util;

/**
 * @author burdakovd
 * 
 */
public final class FiniteSubstitution implements Substitution {

    /**
     * Связки.
     */
    private final Map<Variable, Term> bunches;

    /**
     * @param bunches
     *            набор связок
     */
    public FiniteSubstitution(final Map<Variable, Term> bunches) {
        this.bunches = Collections.unmodifiableMap(new HashMap<Variable, Term>(bunches));
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.Substitution#apply(org.kreved.mathlogic.base
     * .Variable)
     */
    @Override
    public Term apply(final Variable variable) {
        return bunches.containsKey(variable) ? bunches.get(variable) : variable;
    }

    /*
     * (non-Javadoc)
     * 
     * @see java.lang.Object#equals(java.lang.Object)
     */
    @Override
    public boolean equals(final Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final FiniteSubstitution other = (FiniteSubstitution) obj;
        if (bunches == null) {
            if (other.bunches != null) {
                return false;
            }
        } else if (!bunches.equals(other.bunches)) {
            return false;
        }
        return true;
    }

    /*
     * (non-Javadoc)
     * 
     * @see java.lang.Object#hashCode()
     */
    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + (bunches == null ? 0 : bunches.hashCode());
        return result;
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.Substitution#isCorrectFor(org.kreved.mathlogic
     * .base.Formula)
     */
    @Override
    public boolean isCorrectFor(final Formula formula) {

        for (final Entry<Variable, Term> bunch : bunches.entrySet()) {
            if (!formula.isVariableFreeForTerm(bunch.getKey(), bunch.getValue())) {
                return false;
            }
        }

        return true;
    }

    /*
     * (non-Javadoc)
     * 
     * @see java.lang.Object#toString()
     */
    @Override
    public String toString() {

        final List<String> stringBunches = new ArrayList<String>();

        for (final Entry<Variable, Term> bunch : bunches.entrySet()) {
            stringBunches.add(String.format("%s/%s", bunch.getKey(), bunch.getValue()));
        }

        return String.format("{%s}", Util.join(", ", stringBunches));
    }

}
