package org.kreved.mathlogic.util;

/**
 * Функция с заданными типами аргумента и возвращаемого значения.
 * 
 * @param <P>
 *            тип аргумента функции
 * @param <Q>
 *            тип результата функции
 * @author burdakovd
 * 
 */
public interface Function<P, Q> {

    /**
     * Применить функцию к заданному аргументу.
     * 
     * @param argument
     *            аргумент
     * @return значение функции для этого аргумента
     */
    Q apply(P argument);
}
