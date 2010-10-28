package org.kreved.mathlogic.base;

import java.util.List;
import java.util.Map.Entry;

/**
 * Предваренная нормальная форма.
 * 
 * @author burdakovd
 * 
 */
public interface PNF {

    /**
     * Матрица.
     * 
     * @return бескванторная КНФ
     */
    Conjunction<Disjunction<Litera>> getMatrix();

    /**
     * Кванторная приставка.
     * 
     * @return список пар вида "квантор, переменная"
     */
    List<Entry<Quantor, Variable>> getQuantorPrefix();
}
