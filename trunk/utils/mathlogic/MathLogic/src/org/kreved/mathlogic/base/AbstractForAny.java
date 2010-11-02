package org.kreved.mathlogic.base;

import java.util.Collections;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

import org.kreved.mathlogic.util.CommonUtils;

/**
 * @param <I>
 *            тип формулы под квантором
 * @param <S>
 *            тип результата применения подстановки к этой формуле
 * @author burdakovd
 * 
 */
public abstract class AbstractForAny<I extends Formula<? extends I>, S extends Formula<? extends S>>
        extends AbstractQuantifiedFormula<I, S> {

    /**
     * Создаёт формулу "для любого значения variable верно formula".
     * 
     * @param variable
     *            переменная, связываемая квантором
     * @param formula
     *            формула
     */
    public AbstractForAny(final Variable variable, final I formula) {
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
    public final Set<SemanticTable> applyTableDeductionLeft(
            final Iterator<Constant> constantProvider, final Iterator<? extends Term> terms) {

        final Set<Formula<?>> left = new HashSet<Formula<?>>();
        left.add(this);

        while (terms.hasNext()) {
            left.add(getFormula().applySubstitution(
                    new SingleSubstitution(getVariable(), terms.next())));
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
    public final Set<SemanticTable> applyTableDeductionRight(
            final Iterator<Constant> constantProvider, final Iterator<? extends Term> terms) {

        final Constant freshConstant = constantProvider.next();
        final Substitution substitution = new SingleSubstitution(getVariable(), freshConstant);

        return CommonUtils.singleElementSet(new SemanticTable(Collections.<Formula<?>> emptySet(),
                CommonUtils.singleElementSet(getFormula().applySubstitution(substitution))));
    }

}
