package org.kreved.mathlogic.base;

import java.util.Collections;
import java.util.Set;

/**
 * Предметная константа.
 * <p>
 * Имя предмета.
 * 
 * @author burdakovd
 * 
 */
public final class Constant implements Term {

    /**
     * Имя константы.
     */
    private final String name;

    /**
     * @param name
     *            имя константы
     */
    public Constant(final String name) {
        this.name = name;
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
        final Constant other = (Constant) obj;
        if (name == null) {
            if (other.name != null) {
                return false;
            }
        } else if (!name.equals(other.name)) {
            return false;
        }
        return true;
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

    /*
     * (non-Javadoc)
     * 
     * @see org.kreved.mathlogic.base.Term#vars()
     */
    @Override
    public Set<Variable> getVariables() {
        return Collections.emptySet();
    }

}
