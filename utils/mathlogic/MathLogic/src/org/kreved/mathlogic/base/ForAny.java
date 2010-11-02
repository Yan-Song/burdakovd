package org.kreved.mathlogic.base;

/**
 * @param <I>
 *            тип формулы под квантором
 * @author burdakovd
 * 
 */
public final class ForAny<I extends Formula<? extends I>> extends AbstractForAny<I, ForAny<I>> {

    /**
     * @param variable
     *            переменная, связанная квантором
     * @param formula
     *            формула под квантором
     */
    public ForAny(final Variable variable, final I formula) {
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
    protected ForAny<I> create(final Variable variable, final I formula) {
        return new ForAny<I>(variable, formula);
    }

    /*
     * (non-Javadoc)
     * 
     * @see org.kreved.mathlogic.base.Formula#toPrimitive()
     */
    @Override
    public PrimitiveFormula<?> toPrimitive() {
        return new PrimitiveForAny<PrimitiveFormula<?>>(getVariable(), getFormula().toPrimitive());
    }

}
