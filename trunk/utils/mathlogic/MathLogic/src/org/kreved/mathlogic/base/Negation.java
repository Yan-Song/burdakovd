package org.kreved.mathlogic.base;

import java.util.Set;

/**
 * @author burdakovd
 * 
 */
public final class Negation implements Formula {

    /**
     * 
     */
    private static final String NEGATION_SYMBOL = "!";

    /**
     * 
     */
    private final Formula negated;

    /**
     * Создаёт формулу "Неверно, что negated".
     * 
     * @param negated
     *            формула, к которой нужно применить отрицание
     */
    public Negation(final Formula negated) {
        this.negated = negated;
    }

    /*
     * (non-Javadoc)
     * 
     * @see java.lang.Object#equals(java.lang.Object)
     */
    @Override
    public boolean equals(final Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final Negation other = (Negation) obj;
        if (negated == null) {
            if (other.negated != null) {
                return false;
            }
        } else if (!negated.equals(other.negated)) {
            return false;
        }
        return true;
    }

    /*
     * (non-Javadoc)
     * 
     * @see org.kreved.mathlogic.base.Formula#getFreeVariables()
     */
    @Override
    public Set<Variable> getFreeVariables() {
        return negated.getFreeVariables();
    }

    /*
     * (non-Javadoc)
     * 
     * @see java.lang.Object#hashCode()
     */
    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + (negated == null ? 0 : negated.hashCode());
        return result;
    }

    /*
     * (non-Javadoc)
     * 
     * @see java.lang.Object#toString()
     */
    @Override
    public String toString() {
        return String.format("(%s %s)", NEGATION_SYMBOL, negated);
    }
}
