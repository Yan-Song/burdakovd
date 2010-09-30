package org.kreved.mathlogic.base;

/**
 * Отображение из {@link Variable} в {@link Term}.
 * 
 * @author burdakovd
 */
public interface Substitution {

    /**
     * Результат применения подстановки к заданной переменной.
     * 
     * @param variable
     *            переменная
     * @return терм
     */
    Term apply(Variable variable);
}
