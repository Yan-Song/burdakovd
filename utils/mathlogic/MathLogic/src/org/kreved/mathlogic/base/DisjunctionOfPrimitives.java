package org.kreved.mathlogic.base;

import java.util.Collection;
import java.util.List;

/**
 * @param <O>
 *            тип аргументов дизъюнкции
 * @author burdakovd
 * 
 */
public final class DisjunctionOfPrimitives<O extends PrimitiveFormula<? extends O>> extends
        AbstractConjunction<O, DisjunctionOfPrimitives<O>> implements
        PrimitiveFormula<DisjunctionOfPrimitives<O>> {

    /**
     * @param operands
     *            операнды
     */
    public DisjunctionOfPrimitives(final Collection<? extends O> operands) {
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
    protected DisjunctionOfPrimitives<O> create(final List<O> operands) {
        return new DisjunctionOfPrimitives<O>(operands);
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
