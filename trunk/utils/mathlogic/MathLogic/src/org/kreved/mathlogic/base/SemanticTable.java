package org.kreved.mathlogic.base;

import java.util.Collections;
import java.util.HashSet;
import java.util.Set;

/**
 * @author burdakovd
 * 
 */
public final class SemanticTable {
    /**
     * Множество формул, которые мы хотим считать истинными.
     */
    private final Set<Formula> gamma;

    /**
     * Множеств формул, которые мы хотим считатть ложными.
     */
    private final Set<Formula> delta;

    /**
     * @param gamma
     *            Множество формул, которые мы хотим считать истинными.
     * @param delta
     *            Множеств формул, которые мы хотим считатть ложными.
     */
    public SemanticTable(final Set<Formula> gamma, final Set<Formula> delta) {
        this.gamma = Collections.unmodifiableSet(new HashSet<Formula>(gamma));
        this.delta = Collections.unmodifiableSet(new HashSet<Formula>(delta));
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
        final SemanticTable other = (SemanticTable) obj;
        if (delta == null) {
            if (other.delta != null) {
                return false;
            }
        } else if (!delta.equals(other.delta)) {
            return false;
        }
        if (gamma == null) {
            if (other.gamma != null) {
                return false;
            }
        } else if (!gamma.equals(other.gamma)) {
            return false;
        }
        return true;
    }

    /**
     * @return the delta
     */
    public Set<Formula> getDelta() {
        return delta;
    }

    /**
     * @return the gamma
     */
    public Set<Formula> getGamma() {
        return gamma;
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
        result = prime * result + (delta == null ? 0 : delta.hashCode());
        result = prime * result + (gamma == null ? 0 : gamma.hashCode());
        return result;
    }

    /**
     * 
     * @return является ли таблица атомарной.
     */
    public boolean isAtomic() {
        return isAtomic(gamma) && isAtomic(delta);
    }

    /**
     * @param set
     *            множество формул
     * @return все ли формулы в множестве атомарны
     */
    private boolean isAtomic(final Set<Formula> set) {

        for (final Formula formula : set) {
            if (!formula.isAtomic()) {
                return false;
            }
        }

        return true;
    }

    /**
     * 
     * @return закрыта ли таблица
     */
    public boolean isClosed() {

        for (final Formula left : gamma) {
            if (delta.contains(left)) {
                return true;
            }
        }

        return false;
    }

    /*
     * (non-Javadoc)
     * 
     * @see java.lang.Object#toString()
     */
    @Override
    public String toString() {
        return String.format("<%s; %s>", gamma, delta);
    }
}
