package org.kreved.mathlogic.base;

/**
 * @author burdakovd
 * 
 */
public final class ExistsSuch extends AbstractQuantoredFormula {

    /**
     * Создаёт формулу
     * "Существует такое значение variable, для которого верно formula".
     * 
     * @param variable
     *            переменная, связываемая квантором
     * @param formula
     *            формула
     */
    public ExistsSuch(final Variable variable, final Formula formula) {
        super("exists", variable, formula);
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.AbstractQuantoredFormula#create(org.kreved.
     * mathlogic.base.Variable, org.kreved.mathlogic.base.Formula)
     */
    @Override
    protected Formula create(final Variable variable, final Formula formula) {
        return new ExistsSuch(variable, formula);
    }

}
