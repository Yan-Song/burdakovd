package org.kreved.mathlogic.base;

import java.util.Collection;

/**
 * Конъюнкция или дизъюнкция.
 * 
 * @param <O>
 *            тип операндов
 * @param <S>
 *            тип результата применения подстановки к этой формуле
 * @author burdakovd
 * 
 */
public abstract class AbstractPrimitiveOperator<O extends Formula<? extends O>, S extends Formula<? extends S>>
        extends AbstractAssociativeOperator<O, S> {

    /**
     * @param operation
     *            строковое представление оператора
     * @param operands
     *            набор операндов
     */
    public AbstractPrimitiveOperator(final String operation, final Collection<? extends O> operands) {
        super(operation, operands);
    }

}
