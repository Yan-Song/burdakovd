package org.kreved.mathlogic.base;

import java.util.Collection;
import java.util.List;

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

}
