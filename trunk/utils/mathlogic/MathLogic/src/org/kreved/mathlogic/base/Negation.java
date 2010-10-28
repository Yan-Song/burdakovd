package org.kreved.mathlogic.base;

import java.util.Collections;
import java.util.Iterator;
import java.util.Set;

import org.kreved.mathlogic.util.CommonUtils;

/**
 * @param <I>
 *            тип формулы под отрицанием
 * @author burdakovd
 * 
 */
public final class Negation<I extends Formula<? extends I>> extends
        AbstractCompoundFormula<Negation<I>> {

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
    private final I negated;

    /**
     * Создаёт формулу "Неверно, что negated".
     * 
     * @param negated
     *            формула, к которой нужно применить отрицание
     */
    public Negation(final I negated) {
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
    public Negation<I> applySubstitution(final Substitution substitution) {
        return new Negation<I>(negated.applySubstitution(substitution));
    }

    @Override
    public Set<SemanticTable> applyTableDeductionLeft(final Iterator<Constant> constantProvider,
            final Iterable<? extends Term> terms) {
        return CommonUtils.singleElementSet(new SemanticTable(Collections.<Formula<?>> emptySet(),
                CommonUtils.singleElementSet(negated)));
    }

    @Override
    public Set<SemanticTable> applyTableDeductionRight(final Iterator<Constant> constantProvider,
            final Iterable<? extends Term> terms) {
        return CommonUtils.singleElementSet(new SemanticTable(CommonUtils.singleElementSet(negated),
                Collections.<Formula<?>> emptySet()));
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
        final Negation<?> other = (Negation<?>) obj;
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
