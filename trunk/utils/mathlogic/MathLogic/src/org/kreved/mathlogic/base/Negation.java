package org.kreved.mathlogic.base;

/**
 * @param <I>
 *            тип формулы под отрицанием
 * 
 * @author burdakovd
 * 
 */
public final class Negation<I extends Formula<? extends I>> extends
        AbstractNegation<I, Negation<I>> {

    /**
     * @param negated
     *            формула под отрицанием
     */
    public Negation(final I negated) {
        super(negated);
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.AbstractNegation#create(org.kreved.mathlogic
     * .base.Formula)
     */
    @Override
    protected Negation<I> create(final I inner) {
        return new Negation<I>(inner);
    }
}
