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
public abstract class AbstractExistsSuch<I extends Formula<? extends I>, S extends Formula<? extends S>>
        extends AbstractQuantifiedFormula<I, S> {

    /**
     * 
     */
    public static final Quantor QUANTOR = new AbstractQuantor("exists");

    /**
     * Создаёт формулу
     * "Существует такое значение variable, для которого верно formula".
     * 
     * @param variable
     *            переменная, связываемая квантором
     * @param formula
     *            формула
     */
    public AbstractExistsSuch(final Variable variable, final I formula) {
        super(QUANTOR, variable, formula);
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

        final Constant freshConstant = constantProvider.next();
        final Substitution substitution = new SingleSubstitution(getVariable(), freshConstant);

        return CommonUtils.singleElementSet(new SemanticTable(CommonUtils
                .singleElementSet(getFormula().applySubstitution(substitution)), Collections
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

        final Set<Formula<?>> right = new HashSet<Formula<?>>();
        right.add(this);

        while (terms.hasNext()) {
            right.add(getFormula().applySubstitution(
                    new SingleSubstitution(getVariable(), terms.next())));
        }

        return CommonUtils.singleElementSet(new SemanticTable(Collections.<Formula<?>> emptySet(),
                right));
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.AbstractQuantifiedFormula#getNegatedQuantor()
     */
    @Override
    protected final Quantor getNegatedQuantor() {
        return AbstractForAny.QUANTOR;
    }

}
