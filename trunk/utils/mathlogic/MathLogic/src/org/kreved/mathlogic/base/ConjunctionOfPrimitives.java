package org.kreved.mathlogic.base;

import java.util.Collection;
import java.util.List;

/**
 * @param <O>
 *            тип аргументов конъюнкции
 * @author burdakovd
 * 
 */
public final class ConjunctionOfPrimitives<O extends PrimitiveFormula<? extends O>> extends
        AbstractConjunction<O, ConjunctionOfPrimitives<O>> implements
        PrimitiveFormula<ConjunctionOfPrimitives<O>> {

    /**
     * @param operands
     *            операнды
     */
    public ConjunctionOfPrimitives(final Collection<? extends O> operands) {
        super(operands);
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.AbstractMultiOperandOperatorApplication#create
     * (java.util.List)
     */
    @Override
    protected ConjunctionOfPrimitives<O> create(final List<O> operands) {
        return new ConjunctionOfPrimitives<O>(operands);
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.AbstractPrimitiveOperator#createPrimitive(java
     * .util.List)
     */
    @Override
    protected PrimitiveFormula<?> createPrimitive(final List<PrimitiveFormula<?>> operands) {
        return this;
    }

}
