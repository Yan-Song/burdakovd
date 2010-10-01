package org.kreved.mathlogic.base;

/**
 * @author burdakovd
 * 
 */
public final class Implication extends AbstractBinaryFormula {

    /**
     * 
     */
    private static final int PRIORITY = 2;

    /**
     * Создаёт формулу "если left, то right".
     * 
     * @param left
     *            посылка
     * @param right
     *            следствие
     */
    public Implication(final Formula left, final Formula right) {
        super("->", left, right);
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.AbstractBinaryFormula#create(org.kreved.mathlogic
     * .base.Formula, org.kreved.mathlogic.base.Formula)
     */
    @Override
    protected Formula create(final Formula left, final Formula right) {
        return new Implication(left, right);
    }

    /*
     * (non-Javadoc)
     * 
     * @see org.kreved.mathlogic.base.Formula#getPriority()
     */
    @Override
    public int getPriority() {
        return PRIORITY;
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.AbstractBinaryFormula#neededBraces(org.kreved
     * .mathlogic.base.Formula)
     */
    @Override
    protected boolean neededBraces(final Formula part) {
        return part.getPriority() <= getPriority();
    }

}
