package org.kreved.mathlogic.base;


/**
 * @author burdakovd
 * 
 */
public abstract class AbstractCompoundFormula implements Formula {

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
