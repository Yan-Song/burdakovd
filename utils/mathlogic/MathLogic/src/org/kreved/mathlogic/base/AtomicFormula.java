package org.kreved.mathlogic.base;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * Атомарная формула вида P^{(m)}(t_1, t_2, ..., t_m).
 * <ul>
 * <li>P^{(m)} - предикатный символ</li>
 * <li>t_1, t_2, ..., t_m - термы</li>
 * </ul>
 * 
 * @see PredicateSymbol
 * @see Term
 * @author burdakovd
 * 
 */
public final class AtomicFormula implements Formula {

    /**
     * Предикатный cимвол.
     */
    private final PredicateSymbol predicateSymbol;

    /**
     * Список аргументов предиката.
     */
    private final List<Term> arguments;

    /**
     * @param predicateSymbol
     *            предикатный символ
     * @param arguments
     *            список аргументов предиката
     */
    public AtomicFormula(final PredicateSymbol predicateSymbol, final List<Term> arguments) {
        this.predicateSymbol = predicateSymbol;
        this.arguments = Collections.unmodifiableList(new ArrayList<Term>(arguments));
    }

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
        final AtomicFormula other = (AtomicFormula) obj;
        if (arguments == null) {
            if (other.arguments != null) {
                return false;
            }
        } else if (!arguments.equals(other.arguments)) {
            return false;
        }
        if (predicateSymbol == null) {
            if (other.predicateSymbol != null) {
                return false;
            }
        } else if (!predicateSymbol.equals(other.predicateSymbol)) {
            return false;
        }
        return true;
    }

    /**
     * @return the arguments
     */
    public List<Term> getArguments() {
        return arguments;
    }

    /*
     * (non-Javadoc)
     * 
     * @see org.kreved.mathlogic.base.Formula#freeVariables()
     */
    @Override
    public Set<Variable> getFreeVariables() {

        final Set<Variable> ans = new HashSet<Variable>();

        for (final Term argument : arguments) {
            ans.addAll(argument.getVariables());
        }

        return Collections.unmodifiableSet(ans);
    }

    /**
     * @return the predicateSymbol
     */
    public PredicateSymbol getPredicateSymbol() {
        return predicateSymbol;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + (arguments == null ? 0 : arguments.hashCode());
        result = prime * result + (predicateSymbol == null ? 0 : predicateSymbol.hashCode());
        return result;
    }

    /*
     * (non-Javadoc)
     * 
     * @see java.lang.Object#toString()
     */
    @Override
    public String toString() {
        return String.format("%s(%s)", predicateSymbol, Util.join(", ", arguments));
    }
}
