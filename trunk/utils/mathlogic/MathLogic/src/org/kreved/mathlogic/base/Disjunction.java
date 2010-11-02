package org.kreved.mathlogic.base;

import java.util.Collection;
import java.util.List;

import org.kreved.mathlogic.util.Function;
import org.kreved.mathlogic.util.Functional;

/**
 * @param <O>
 *            тип аргументов дизъюнкции
 * @author burdakovd
 * 
 */
public final class Disjunction<O extends Formula<? extends O>> extends
        AbstractDisjunction<O, Disjunction<O>> {

    /**
     * @param operands
     *            операнды
     */
    public Disjunction(final Collection<? extends O> operands) {
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
    protected Disjunction<O> create(final List<O> operands) {
        return new Disjunction<O>(operands);
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
        return new DisjunctionOfPrimitives<PrimitiveFormula<?>>(Functional.mapList(getOperands(),
                new Function<O, PrimitiveFormula<?>>() {

                    @Override
                    public PrimitiveFormula<?> apply(final O argument) {
                        return argument.toPrimitive();
                    }
                }));
    }

}
