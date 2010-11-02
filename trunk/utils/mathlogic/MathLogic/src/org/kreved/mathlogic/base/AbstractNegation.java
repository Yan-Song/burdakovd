package org.kreved.mathlogic.base;

import java.util.Collections;
import java.util.Iterator;
import java.util.Set;

import org.kreved.mathlogic.util.CommonUtils;
import org.kreved.mathlogic.util.Function;

/**
 * @param <I>
 *            тип формулы под отрицанием
 * @param <S>
 *            тип результата применения подстановки к этой формуле
 * @author burdakovd
 * 
 */
public abstract class AbstractNegation<I extends Formula<? extends I>, S extends Formula<? extends S>>
        extends AbstractCompoundFormula<S> {

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
    public AbstractNegation(final I negated) {
        super(NEGATION_SYMBOL);
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
    public final S applySubstitution(final Substitution substitution) {
        return create(negated.applySubstitution(substitution));
    }

    @Override
    public final Set<SemanticTable> applyTableDeductionLeft(
            final Iterator<Constant> constantProvider, final Iterator<? extends Term> terms) {
        return CommonUtils.singleElementSet(new SemanticTable(Collections.<Formula<?>> emptySet(),
                CommonUtils.singleElementSet(negated)));
    }

    @Override
    public final Set<SemanticTable> applyTableDeductionRight(
            final Iterator<Constant> constantProvider, final Iterator<? extends Term> terms) {
        return CommonUtils.singleElementSet(new SemanticTable(
                CommonUtils.singleElementSet(negated), Collections.<Formula<?>> emptySet()));
    }

    /**
     * @param inner
     *            формула
     * @return её отрицание
     */
    protected abstract S create(I inner);

    /*
     * (non-Javadoc)
     * 
     * @see java.lang.Object#equals(java.lang.Object)
     */
    @Override
    public final boolean equals(final Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null) {
            return false;
        }
        if (!AbstractNegation.class.isInstance(obj)) {
            return false;
        }
        final AbstractNegation<?, ?> other = (AbstractNegation<?, ?>) obj;
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
    public final Set<Constant> getConstants() {
        return negated.getConstants();
    }

    /*
     * (non-Javadoc)
     * 
     * @see org.kreved.mathlogic.base.Formula#getFreeVariables()
     */
    @Override
    public final Set<Variable> getFreeVariables() {
        return negated.getFreeVariables();
    }

    /**
     * @return the negated
     */
    public final I getNegated() {
        return negated;
    }

    /*
     * (non-Javadoc)
     * 
     * @see org.kreved.mathlogic.base.Formula#getPriority()
     */
    @Override
    public final int getPriority() {
        return PRIORITY;
    }

    /*
     * (non-Javadoc)
     * 
     * @see java.lang.Object#hashCode()
     */
    @Override
    public final int hashCode() {
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
    public final boolean isVariableFreeForTerm(final Variable variable, final Term term) {
        return negated.isVariableFreeForTerm(variable, term);
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.Formula#renameVariables(org.kreved.mathlogic
     * .util.Function)
     */
    @Override
    public final S renameVariables(final Function<Variable, Variable> renamer) {
        return create(negated.renameVariables(renamer));
    }

    /*
     * (non-Javadoc)
     * 
     * @see java.lang.Object#toString()
     */
    @Override
    public final String toString() {
        return String.format(negated.getPriority() > getPriority() ? "%s%s" : "%s(%s)",
                NEGATION_SYMBOL, negated);
    }
}
