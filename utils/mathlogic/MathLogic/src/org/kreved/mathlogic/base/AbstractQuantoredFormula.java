package org.kreved.mathlogic.base;

import java.util.Set;

/**
 * @author burdakovd
 * 
 */
public class AbstractQuantoredFormula implements Formula {

    /**
     * Строковое представление квантора. Используется для hashCode, equals,
     * toString
     */
    private final String quantor;

    /**
     * Переменная, связуемая квантором.
     */
    private final Variable variable;

    /**
     * Формула, к которой прменяется квантор.
     */
    private final Formula formula;

    /**
     * @param quantor
     *            Строковое представление квантора. Используется для hashCode,
     *            equals, toString
     * @param variable
     *            Переменная, связуемая квантором.
     * @param formula
     *            Формула, к которой прменяется квантор.
     */
    public AbstractQuantoredFormula(final String quantor, final Variable variable,
            final Formula formula) {

        this.quantor = quantor;
        this.variable = variable;
        this.formula = formula;
    }

    /*
     * (non-Javadoc)
     * 
     * @see java.lang.Object#equals(java.lang.Object)
     */
    @Override
    public final boolean equals(final Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final AbstractQuantoredFormula other = (AbstractQuantoredFormula) obj;
        if (formula == null) {
            if (other.formula != null) {
                return false;
            }
        } else if (!formula.equals(other.formula)) {
            return false;
        }
        if (quantor == null) {
            if (other.quantor != null) {
                return false;
            }
        } else if (!quantor.equals(other.quantor)) {
            return false;
        }
        if (variable == null) {
            if (other.variable != null) {
                return false;
            }
        } else if (!variable.equals(other.variable)) {
            return false;
        }
        return true;
    }

    /**
     * @return the formula
     */
    public final Formula getFormula() {
        return formula;
    }

    /*
     * (non-Javadoc)
     * 
     * @see org.kreved.mathlogic.base.Formula#freeVariables()
     */
    @Override
    public final Set<Variable> getFreeVariables() {
        return Util.excluding(formula.getFreeVariables(), variable);
    }

    /**
     * @return the quantor
     */
    public final String getQuantor() {
        return quantor;
    }

    /**
     * @return the variable
     */
    public final Variable getVariable() {
        return variable;
    }

    /*
     * (non-Javadoc)
     * 
     * @see java.lang.Object#hashCode()
     */
    @Override
    public final int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + (formula == null ? 0 : formula.hashCode());
        result = prime * result + (quantor == null ? 0 : quantor.hashCode());
        result = prime * result + (variable == null ? 0 : variable.hashCode());
        return result;
    }

    /*
     * (non-Javadoc)
     * 
     * @see java.lang.Object#toString()
     */
    @Override
    public final String toString() {
        return String.format("(%s %s %s)", quantor, variable, formula);
    }

}
