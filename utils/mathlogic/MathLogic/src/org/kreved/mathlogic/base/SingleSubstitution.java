package org.kreved.mathlogic.base;

/**
 * @author burdakovd
 * 
 */
public final class SingleSubstitution implements Substitution {

    /**
     * 
     */
    private final Variable variable;

    /**
     * 
     */
    private final Term term;

    /**
     * @param variable
     *            переменная, которую нужно заменять
     * @param term
     *            терм, на который нужно заменять
     */
    public SingleSubstitution(final Variable variable, final Term term) {
        this.variable = variable;
        this.term = term;
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.Substitution#apply(org.kreved.mathlogic.base
     * .Variable)
     */
    @Override
    public Term apply(final Variable variable) {
        if (variable.equals(this.variable)) {
            return term;
        } else {
            return variable;
        }
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.Substitution#isCorrectFor(org.kreved.mathlogic
     * .base.Formula)
     */
    @Override
    public boolean isCorrectFor(final Formula formula) {
        return formula.isVariableFreeForTerm(variable, term);
    }

}
