package org.kreved.mathlogic.base;

/**
 * @author burdakovd
 * 
 */
public final class Conjunction extends AbstractBinaryFormula {

    /**
     * Создаёт формулу "left и right".
     * 
     * @param left
     *            левая часть
     * @param right
     *            правая часть
     */
    public Conjunction(final Formula left, final Formula right) {
        super("&", left, right);
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
        return new Conjunction(left, right);
    }

}
