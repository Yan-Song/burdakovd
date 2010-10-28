package org.kreved.mathlogic.base;

/**
 * @param <T>
 *            тип результата применения подстановки к этой формуле
 * @author burdakovd
 * 
 */
public abstract class AbstractCompoundFormula<T extends Formula<?>> implements Formula<T> {

    /**
     * Строковое представление символа формулы.
     * <p>
     * Используется для преобразования формулы в строку, для вычисления хэша и
     * для сравнения формул.
     */
    private final String symbol;

    /**
     * @param symbol
     *            строковое представление оператора
     */
    public AbstractCompoundFormula(final String symbol) {
        this.symbol = symbol;
    }

    /*
     * (non-Javadoc)
     * 
     * @see org.kreved.mathlogic.base.Formula#isAtomic()
     */
    @Override
    public final boolean isAtomic() {
        return false;
    }

    /*
     * (non-Javadoc)
     * 
     * @see org.kreved.mathlogic.base.Formula#symbol()
     */
    @Override
    public final String symbol() {
        return symbol;
    }

}
