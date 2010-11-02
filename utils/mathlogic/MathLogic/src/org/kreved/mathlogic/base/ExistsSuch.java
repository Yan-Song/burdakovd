package org.kreved.mathlogic.base;


/**
 * @param <I>
 *            тип формулы под квантором
 * @author burdakovd
 * 
 */
public final class ExistsSuch<I extends Formula<? extends I>> extends
        AbstractExistsSuch<I, ExistsSuch<I>> {

    /**
     * @param variable
     *            переменная, связанная квантором
     * @param formula
     *            формула под квантором
     */
    public ExistsSuch(final Variable variable, final I formula) {
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
    protected ExistsSuch<I> create(final Variable variable, final I formula) {
        return new ExistsSuch<I>(variable, formula);
    }

}
