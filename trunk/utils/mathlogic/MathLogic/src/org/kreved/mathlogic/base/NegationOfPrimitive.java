package org.kreved.mathlogic.base;

/**
 * @param <I>
 *            тип формулы под отрицанием
 * 
 * @author burdakovd
 * 
 */
public final class NegationOfPrimitive<I extends PrimitiveFormula<? extends I>> extends
        AbstractNegation<I, NegationOfPrimitive<I>> implements
        PrimitiveFormula<NegationOfPrimitive<I>> {

    /**
     * @param negated
     *            формула под отрицанием
     */
    public NegationOfPrimitive(final I negated) {
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
    protected NegationOfPrimitive<I> create(final I inner) {
        return new NegationOfPrimitive<I>(inner);
    }

    /*
     * (non-Javadoc)
     * 
     * @see org.kreved.mathlogic.base.Formula#toPrimitive()
     */
    @Override
    public PrimitiveFormula<?> toPrimitive() {
        return this;
    }

}
