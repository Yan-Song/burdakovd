package org.kreved.mathlogic.base;

/**
 * @author burdakovd
 * 
 */
public abstract class AbstractBinaryAssociativeFormula extends AbstractBinaryFormula {

    /**
     * @param operation
     *            строковое представление операции
     * @param left
     *            левая часть
     * @param right
     *            правая часть
     */
    public AbstractBinaryAssociativeFormula(final String operation, final Formula left,
            final Formula right) {

        super(operation, left, right);
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.AbstractBinaryFormula#neededBraces(org.kreved
     * .mathlogic.base.Formula)
     */
    @Override
    protected final boolean neededBraces(final Formula part) {
        return part.getPriority() < getPriority();
    }

}
