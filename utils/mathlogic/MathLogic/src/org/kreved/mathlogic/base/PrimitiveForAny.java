package org.kreved.mathlogic.base;

/**
 * @param <I>
 *            тип формулы под квантором
 * @author burdakovd
 * 
 */
public final class PrimitiveForAny<I extends PrimitiveFormula<? extends I>> extends
        AbstractForAny<I, PrimitiveForAny<I>> implements PrimitiveFormula<PrimitiveForAny<I>> {

    /**
     * @param variable
     *            связанная квантором переменная
     * @param formula
     *            формула под квантором
     */
    public PrimitiveForAny(final Variable variable, final I formula) {
        super(variable, formula);
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.AbstractQuantifiedFormula#create(org.kreved
     * .mathlogic.base.Variable, org.kreved.mathlogic.base.Formula)
     */
    @Override
    protected PrimitiveForAny<I> create(final Variable variable, final I formula) {
        return new PrimitiveForAny<I>(variable, formula);
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
