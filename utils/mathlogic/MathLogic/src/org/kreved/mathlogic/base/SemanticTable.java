package org.kreved.mathlogic.base;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import org.kreved.mathlogic.util.MathUtil;

/**
 * @author burdakovd
 * 
 */
public final class SemanticTable implements HasConstants {
    /**
     * Множество формул, которые мы хотим считать истинными.
     */
    private final List<Formula> gamma;

    /**
     * Множеств формул, которые мы хотим считатть ложными.
     */
    private final List<Formula> delta;

    /**
     * @param gamma
     *            Множество формул, которые мы хотим считать истинными.
     * @param delta
     *            Множеств формул, которые мы хотим считатть ложными.
     */
    public SemanticTable(final Collection<? extends Formula> gamma,
            final Collection<? extends Formula> delta) {

        this.gamma = Collections.unmodifiableList(new ArrayList<Formula>(gamma));
        this.delta = Collections.unmodifiableList(new ArrayList<Formula>(delta));
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
     * 
     * @return множество констант, использованных в таблице
     */
    @Override
    public Set<Constant> getConstants() {

        final Set<Constant> ans = new HashSet<Constant>();

        for (final Formula formula : gamma) {
            ans.addAll(formula.getConstants());
        }

        for (final Formula formula : delta) {
            ans.addAll(formula.getConstants());
        }

        return Collections.unmodifiableSet(ans);
    }

    /**
     * @return the delta
     */
    public List<Formula> getDelta() {
        return delta;
    }

    /**
     * @return the gamma
     */
    public List<Formula> getGamma() {
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
     * @param gamma
     *            множество формул
     * @return все ли формулы в множестве атомарны
     */
    private boolean isAtomic(final List<Formula> gamma) {

        for (final Formula formula : gamma) {
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

        final Set<Formula> sDelta = new HashSet<Formula>(delta);

        for (final Formula left : gamma) {
            if (sDelta.contains(left)) {
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
        return String.format("< %s | %s >", gamma.isEmpty() ? "null" : MathUtil.join(", ", gamma),
                delta.isEmpty() ? "null" : MathUtil.join(", ", delta));
    }
}
