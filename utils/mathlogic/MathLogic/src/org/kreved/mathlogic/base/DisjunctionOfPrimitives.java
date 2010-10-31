package org.kreved.mathlogic.base;

import java.util.Collection;
import java.util.List;

/**
 * @author burdakovd
 * 
 */
public final class DisjunctionOfPrimitives<O extends PrimitiveFormula<? extends O>> extends
        AbstractConjunction<O, DisjunctionOfPrimitives<O>> implements
        PrimitiveFormula<DisjunctionOfPrimitives<O>> {

    /**
     * @param operands
     */
    public DisjunctionOfPrimitives(final Collection<? extends O> operands) {
        super(operands);
        // TODO Auto-generated constructor stub
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
        // TODO Auto-generated method stub
        return null;
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
        // TODO Auto-generated method stub
        return null;
    }

}
