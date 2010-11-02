package org.kreved.mathlogic.base;

/**
 * Атомарная формула, либо отрицание атомарной формулы.
 * 
 * @param <T>
 *            тип результата применения подстановки к литере
 * @author burdakovd
 * 
 */
public interface Litera<T extends Litera<? extends T>> extends PrimitiveFormula<T> {

}
