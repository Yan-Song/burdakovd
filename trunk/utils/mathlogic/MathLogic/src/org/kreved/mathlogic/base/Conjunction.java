package org.kreved.mathlogic.base;

import java.util.Collection;
import java.util.List;

import org.kreved.mathlogic.util.Function;
import org.kreved.mathlogic.util.Functional;

/**
 * @param <O>
 *            тип аргументов конъюнкции
 * @author burdakovd
 * 
 */
public final class Conjunction<O extends Formula<? extends O>> extends
        AbstractConjunction<O, Conjunction<O>> {

    /**
     * @param operands
     *            операнды
     */
    public Conjunction(final Collection<? extends O> operands) {
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
    protected Conjunction<O> create(final List<O> operands) {
        return new Conjunction<O>(operands);
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
        return new ConjunctionOfPrimitives<PrimitiveFormula<?>>(Functional.mapList(getOperands(),
                new Function<O, PrimitiveFormula<?>>() {

                    @Override
                    public PrimitiveFormula<?> apply(final O argument) {
                        return argument.toPrimitive();
                    }
                }));
    }

}
