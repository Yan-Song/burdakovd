package org.kreved.mathlogic.util;

/**
 * Функция с заданным типом аргумента, возращающая <code>true</code> или
 * <code>false</code>.
 * 
 * @param <T>
 *            тип аргумента функции
 * @author burdakovd
 * 
 */
public interface Predicate<T> {

    /**
     * Применить функцию к заданному аргументу.
     * 
     * @param argument
     *            аргумент
     * @return значение функции для этого аргумента
     */
    boolean apply(T argument);
}
