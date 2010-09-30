package org.kreved.mathlogic.base;

/**
 * @author burdakovd
 * 
 */
public final class Disjunction extends AbstractBinaryFormula {

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

}
