package org.kreved.mathlogic.base;

/**
 * @author burdakovd
 * 
 */
public final class Disjunction extends AbstractBinaryAssociativeFormula {

    /**
     * 
     */
    private static final int PRIORITY = 3;

    /**
     * Создаёт формулу "left или right".
     * 
     * @param left
     *            левая часть дизъюнкции
     * @param right
     *            правая часть дизъюнкции
     */
    public Disjunction(final Formula left, final Formula right) {
        super("V", left, right);
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
        return new Disjunction(left, right);
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

}
