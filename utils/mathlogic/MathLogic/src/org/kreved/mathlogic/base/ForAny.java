package org.kreved.mathlogic.base;

/**
 * @author burdakovd
 * 
 */
public final class ForAny extends AbstractQuantoredFormula {

    /**
     * Создаёт формулу "для любого значения variable верно formula".
     * 
     * @param variable
     *            переменная, связываемая квантором
     * @param formula
     *            формула
     */
    public ForAny(final Variable variable, final Formula formula) {
        super("any", variable, formula);
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
        return new ForAny(variable, formula);
    }

}
