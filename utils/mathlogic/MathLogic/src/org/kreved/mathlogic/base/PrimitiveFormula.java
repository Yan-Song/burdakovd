package org.kreved.mathlogic.base;

/**
 * Формула, удовлетворяющая следующим условиям.
 * 
 * <ul>
 * <li>составлена из атомарных формул с использованием только конъюнкции,
 * дизъюнкции и отрицания</li>
 * <li>
 * отрицание применяется только к атомарным формулам</li>
 * <li>кванторов нет</li>
 * </ul>
 * 
 * @param <S>
 *            тип результата применения подстановки к этой формуле
 * @author burdakovd
 * 
 */
public interface PrimitiveFormula<S extends PrimitiveFormula<?>> extends Formula<S> {

}
