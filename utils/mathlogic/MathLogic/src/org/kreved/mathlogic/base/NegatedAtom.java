package org.kreved.mathlogic.base;


/**
 * @author burdakovd
 * 
 */
public final class NegatedAtom extends AbstractNegation<AtomicFormula, NegatedAtom> implements
        Litera<NegatedAtom> {

    /**
     * @param negated
     *            атом под отрицанием
     */
    public NegatedAtom(final AtomicFormula negated) {
        super(negated);
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.AbstractNegation#create(org.kreved.mathlogic
     * .base.Formula)
     */
    @Override
    protected NegatedAtom create(final AtomicFormula inner) {
        return new NegatedAtom(inner);
    }

}
