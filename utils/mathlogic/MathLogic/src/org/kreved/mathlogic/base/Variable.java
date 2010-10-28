package org.kreved.mathlogic.base;

import java.util.Collections;
import java.util.Set;

import org.kreved.mathlogic.util.CommonUtils;

/**
 * Предметная переменная.
 * 
 * @author burdakovd
 * 
 */
public final class Variable implements Term {

    /**
     * Имя переменной.
     */
    private final String name;

    /**
     * @param name
     *            имя переменной
     */
    public Variable(final String name) {
        this.name = name;
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.Substitutable#applySubstitution(org.kreved.
     * mathlogic.base.Substitution)
     */
    @Override
    public Term applySubstitution(final Substitution substitution) {
        return substitution.apply(this);
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
        final Variable other = (Variable) obj;
        if (name == null) {
            if (other.name != null) {
                return false;
            }
        } else if (!name.equals(other.name)) {
            return false;
        }
        return true;
    }

    /*
     * (non-Javadoc)
     * 
     * @see org.kreved.mathlogic.base.HasConstants#getConstants()
     */
    @Override
    public Set<Constant> getConstants() {
        return Collections.emptySet();
    }

    /**
     * @return the name
     */
    public String getName() {
        return name;
    }

    /*
     * (non-Javadoc)
     * 
     * @see org.kreved.mathlogic.base.Term#vars()
     */
    @Override
    public Set<Variable> getVariables() {
        return CommonUtils.singleElementSet(this);
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
        result = prime * result + (name == null ? 0 : name.hashCode());
        return result;
    }

    /*
     * (non-Javadoc)
     * 
     * @see java.lang.Object#toString()
     */
    @Override
    public String toString() {
        return name;
    }

}
