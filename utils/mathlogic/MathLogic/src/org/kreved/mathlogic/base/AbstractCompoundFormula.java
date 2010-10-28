package org.kreved.mathlogic.base;

/**
 * @param <T>
 *            тип результата применения подстановки к этой формуле
 * @author burdakovd
 * 
 */
public abstract class AbstractCompoundFormula<T extends Formula<?>> implements Formula<T> {

    /*
     * (non-Javadoc)
     * 
     * @see org.kreved.mathlogic.base.Formula#isAtomic()
     */
    @Override
    public final boolean isAtomic() {
        return false;
    }

}
