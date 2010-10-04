package org.kreved.mathlogic.base;

import java.util.Collections;
import java.util.Iterator;
import java.util.Set;

import org.kreved.mathlogic.util.MathUtil;

/**
 * @author burdakovd
 * 
 */
public final class Negation extends AbstractCompoundFormula {

    /**
     * 
     */
    private static final int PRIORITY = 6;

    /**
     * 
     */
    private static final String NEGATION_SYMBOL = "!";

    /**
     * 
     */
    private final Formula negated;

    /**
     * Создаёт формулу "Неверно, что negated".
     * 
     * @param negated
     *            формула, к которой нужно применить отрицание
     */
    public Negation(final Formula negated) {
        this.negated = negated;
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.Substitutable#applySubstitution(org.kreved.
     * mathlogic.base.Substitution)
     */
    @Override
    public Formula applySubstitution(final Substitution substitution) {
        return new Negation(negated.applySubstitution(substitution));
    }

    @Override
    public Set<SemanticTable> applyTableDeductionLeft(final Iterator<Constant> constantProvider,
            final Iterable<? extends Term> terms) {
        return MathUtil.unmodifiableSet(new SemanticTable(Collections.<Formula> emptySet(),
                MathUtil.unmodifiableSet(negated)));
    }

    @Override
    public Set<SemanticTable> applyTableDeductionRight(final Iterator<Constant> constantProvider,
            final Iterable<? extends Term> terms) {
        return MathUtil.unmodifiableSet(new SemanticTable(MathUtil.unmodifiableSet(negated),
                Collections.<Formula> emptySet()));
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
        final Negation other = (Negation) obj;
        if (negated == null) {
            if (other.negated != null) {
                return false;
            }
        } else if (!negated.equals(other.negated)) {
            return false;
        }
        return true;
    }

    /*
     * (non-Javadoc)
     * 
     * @see org.kreved.mathlogic.base.Formula#getConstants()
     */
    @Override
    public Set<Constant> getConstants() {
        return negated.getConstants();
    }

    /*
     * (non-Javadoc)
     * 
     * @see org.kreved.mathlogic.base.Formula#getFreeVariables()
     */
    @Override
    public Set<Variable> getFreeVariables() {
        return negated.getFreeVariables();
    }

    /*
     * (non-Javadoc)
     * 
     * @see org.kreved.mathlogic.base.Formula#getPriority()
     */
    @Override
    public int getPriority() {
        return PRIORITY;
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
        result = prime * result + (negated == null ? 0 : negated.hashCode());
        return result;
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.Formula#isVariableFreeForTerm(org.kreved.mathlogic
     * .base.Variable, org.kreved.mathlogic.base.Term)
     */
    @Override
    public boolean isVariableFreeForTerm(final Variable variable, final Term term) {
        return negated.isVariableFreeForTerm(variable, term);
    }

    /*
     * (non-Javadoc)
     * 
     * @see java.lang.Object#toString()
     */
    @Override
    public String toString() {
        return String.format(negated.getPriority() > getPriority() ? "%s%s" : "%s(%s)",
                NEGATION_SYMBOL, negated);
    }
}
