package org.kreved.mathlogic.base;

/**
 * @param <I>
 *            тип формулы под квантором
 * @author burdakovd
 * 
 */
public final class PrimitiveExistsSuch<I extends PrimitiveFormula<? extends I>> extends
        AbstractExistsSuch<I, PrimitiveExistsSuch<I>> implements
        PrimitiveFormula<PrimitiveExistsSuch<I>> {

    /**
     * @param variable
     *            связанная квантором переменная
     * @param formula
     *            формула под квантором
     */
    public PrimitiveExistsSuch(final Variable variable, final I formula) {
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
    protected PrimitiveExistsSuch<I> create(final Variable variable, final I formula) {
        return new PrimitiveExistsSuch<I>(variable, formula);
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
