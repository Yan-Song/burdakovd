package org.kreved.mathlogic.base;

/**
 * @author burdakovd
 * 
 */
public class ForAny extends AbstractQuantoredFormula {

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

}
