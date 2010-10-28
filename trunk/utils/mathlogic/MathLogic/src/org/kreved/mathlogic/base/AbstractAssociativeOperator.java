package org.kreved.mathlogic.base;

import java.util.Collection;

/**
 * @param <O>
 *            тип операндов
 * @param <S>
 *            тип результата применения подстановки к этой формуле
 * @author burdakovd
 * 
 */
public abstract class AbstractAssociativeOperator<O extends Formula<? extends O>, S extends Formula<?>>
        extends AbstractMultiOperandOperatorApplication<O, S> {

    /**
     * @param operation
     *            строковое представление оператора
     * @param operands
     *            набор операндов
     */
    public AbstractAssociativeOperator(final String operation,
            final Collection<? extends O> operands) {
        super(operation, operands);
    }

    /*
     * (non-Javadoc)
     * 
     * @see org.kreved.mathlogic.base.AbstractMultiOperandOperatorApplication#
     * neededBraces(org.kreved.mathlogic.base.Formula)
     */
    @Override
    protected final boolean neededBraces(final O operand) {
        return operand.getPriority() < getPriority();
    }

}
