package org.kreved.mathlogic.base;

/**
 * Формула, составленная из атомарных формул с использованиемм только
 * конъюнкции, дизъюнкции и отрицания.
 * 
 * @param <S>
 *            тип результата применения подстановки к этой формуле
 * @author burdakovd
 * 
 */
public interface PrimitiveFormula<S extends PrimitiveFormula<?>> extends Formula<S> {

}
