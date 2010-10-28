package org.kreved.mathlogic.base;

import java.util.Collections;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

import org.kreved.mathlogic.util.CommonUtils;

/**
 * @param <I>
 *            тип формулы под квантором
 * @author burdakovd
 * 
 */
public final class ForAny<I extends Formula<? extends I>> extends
        AbstractQuantifiedFormula<I, ForAny<I>> {

    /**
     * Создаёт формулу "для любого значения variable верно formula".
     * 
     * @param variable
     *            переменная, связываемая квантором
     * @param formula
     *            формула
     */
    public ForAny(final Variable variable, final I formula) {
        super("any", variable, formula);
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

        final Set<Formula<?>> left = new HashSet<Formula<?>>();
        left.add(this);

        for (final Term term : terms) {
            left.add(getFormula().applySubstitution(new SingleSubstitution(getVariable(), term)));
        }

        return CommonUtils.singleElementSet(new SemanticTable(left, Collections
                .<Formula<?>> emptySet()));
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

        final Constant freshConstant = constantProvider.next();
        final Substitution substitution = new SingleSubstitution(getVariable(), freshConstant);

        return CommonUtils.singleElementSet(new SemanticTable(Collections.<Formula<?>> emptySet(),
                CommonUtils.singleElementSet(getFormula().applySubstitution(substitution))));
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.AbstractQuantifiedFormula#create(org.kreved
     * .mathlogic.base.Variable, org.kreved.mathlogic.base.Formula)
     */
    @Override
    protected ForAny<I> create(final Variable variable, final I formula) {
        return new ForAny<I>(variable, formula);
    }

}
