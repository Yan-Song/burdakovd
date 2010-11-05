package org.kreved.mathlogic.base;

import org.kreved.mathlogic.util.Of;

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

    /*
     * (non-Javadoc)
     * 
     * @see org.kreved.mathlogic.base.PrimitiveFormula#makeCNF()
     */
    @Override
    public Conjunction<Disjunction<Litera<?>>> makeCNF() {
        return new Conjunction<Disjunction<Litera<?>>>(
                Of.of(new Disjunction<Litera<?>>(Of.of(this))));
    }

}
