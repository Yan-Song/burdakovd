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

    /**
     * По определению подстановка называется правильной для формулы
     * <code>phi</code>, если для любой связки <code>x_i/t_i</code> переменная
     * <code>x_i</code> свободня для терма <code>t_i</code> в формуле
     * <code>phi</code>.
     * 
     * @param formula
     *            формула, для которой нужно проверить корректность этой
     *            подстановки
     * @return правильна ли эта подстановка для заданной формулы.
     */
    boolean isCorrectFor(Formula<?> formula);
}
