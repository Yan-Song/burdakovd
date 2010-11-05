package org.kreved.mathlogic.base;

import java.util.List;
import java.util.Map.Entry;

/**
 * Предваренная нормальная форма.
 * 
 * @author burdakovd
 * 
 */
public final class PNF {

    /**
     * 
     */
    private final Conjunction<Disjunction<Litera<?>>> matrix;

    /**
     * 
     */
    private final List<? extends Entry<Quantor, Variable>> prefix;

    /**
     * @param matrix
     *            матрица (КНФ)
     * @param prefix
     *            кванторный префикс
     */
    public PNF(final Conjunction<Disjunction<Litera<?>>> matrix,
            final List<? extends Entry<Quantor, Variable>> prefix) {
        this.matrix = matrix;
        this.prefix = prefix;
    }

    /**
     * Матрица.
     * 
     * @return бескванторная КНФ
     */
    public Conjunction<Disjunction<Litera<?>>> getMatrix() {
        return matrix;
    }

    /**
     * Кванторная приставка.
     * 
     * @return список пар вида "квантор, переменная"
     */
    public List<? extends Entry<Quantor, Variable>> getQuantorPrefix() {
        return prefix;
    }
}
