package org.kreved.mathlogic.base;

/**
 * @author burdakovd
 * 
 */
public class ExistsSuch extends AbstractQuantoredFormula {

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

}
