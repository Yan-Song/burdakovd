package org.kreved.mathlogic.base;

import java.util.Collections;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

import org.kreved.mathlogic.util.MathUtil;

/**
 * @author burdakovd
 * 
 */
public final class ExistsSuch extends AbstractQuantifiedFormula {

    /**
     * Создаёт формулу
     * "Существует такое значение variable, для которого верно formula".
     * 
     * @param variable
     *            переменная, связываемая квантором
     * @param formula
     *            формула
     */
    public ExistsSuch(final Variable variable, final Formula formula) {
        super("exists", variable, formula);
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.Formula#applyTableDeductionLeft(java.util.Iterator
     * )
     */
    @Override
    public Set<SemanticTable> applyTableDeductionLeft(final Iterator<Constant> constantProvider,
            final Iterable<? extends Term> terms) {

        final Constant freshConstant = constantProvider.next();
        final Substitution substitution = new SingleSubstitution(getVariable(), freshConstant);

        return MathUtil.unmodifiableSet(new SemanticTable(MathUtil.unmodifiableSet(getFormula()
                .applySubstitution(substitution)), Collections.<Formula> emptySet()));
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.Formula#applyTableDeductionRight(java.util.
     * Iterator)
     */
    @Override
    public Set<SemanticTable> applyTableDeductionRight(final Iterator<Constant> constantProvider,
            final Iterable<? extends Term> terms) {

        final Set<Formula> right = new HashSet<Formula>();
        right.add(this);

        for (final Term term : terms) {
            right.add(getFormula().applySubstitution(new SingleSubstitution(getVariable(), term)));
        }

        return MathUtil.unmodifiableSet(new SemanticTable(Collections.<Formula> emptySet(), right));
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.AbstractQuantifiedFormula#create(org.kreved.
     * mathlogic.base.Variable, org.kreved.mathlogic.base.Formula)
     */
    @Override
    protected Formula create(final Variable variable, final Formula formula) {
        return new ExistsSuch(variable, formula);
    }

}
