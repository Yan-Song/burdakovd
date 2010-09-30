package org.kreved.mathlogic.base;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * Составной терм.
 * <p>
 * <code>f^{(n)}(t_1, t_2, ..., t_n)</code>
 * <ul>
 * <li>t_1, t_2, ..., t_n - термы</li>
 * <li>f^{(n)} - функциональный символ</li>
 * </ul>
 * 
 * @see FunctionalSymbol
 * @author burdakovd
 * 
 */
public final class CompoundTerm implements Term {

    /**
     * Функциональный символ.
     */
    private final FunctionalSymbol functionalSymbol;

    /**
     * Список аргументов.
     */
    private final List<Term> arguments;

    /**
     * @param functionalSymbol
     *            функциональный символ
     * @param arguments
     *            списк аргументов
     */
    public CompoundTerm(final FunctionalSymbol functionalSymbol, final List<Term> arguments) {
        this.functionalSymbol = functionalSymbol;
        this.arguments = Collections.unmodifiableList(new ArrayList<Term>(arguments));
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
        final CompoundTerm other = (CompoundTerm) obj;
        if (arguments == null) {
            if (other.arguments != null) {
                return false;
            }
        } else if (!arguments.equals(other.arguments)) {
            return false;
        }
        if (functionalSymbol == null) {
            if (other.functionalSymbol != null) {
                return false;
            }
        } else if (!functionalSymbol.equals(other.functionalSymbol)) {
            return false;
        }
        return true;
    }

    /*
     * (non-Javadoc)
     * 
     * @see org.kreved.mathlogic.base.Term#vars()
     */
    @Override
    public Set<Variable> getVariables() {

        final Set<Variable> answer = new HashSet<Variable>();

        for (final Term argument : arguments) {
            answer.addAll(argument.getVariables());
        }

        return Collections.unmodifiableSet(answer);
    }

    /**
     * @return the arguments
     */
    public List<Term> getArguments() {
        return arguments;
    }

    /**
     * @return the functionalSymbol
     */
    public FunctionalSymbol getFunctionalSymbol() {
        return functionalSymbol;
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
        result = prime * result + (arguments == null ? 0 : arguments.hashCode());
        result = prime * result + (functionalSymbol == null ? 0 : functionalSymbol.hashCode());
        return result;
    }

    /*
     * (non-Javadoc)
     * 
     * @see java.lang.Object#toString()
     */
    @Override
    public String toString() {
        return String.format("%s(%s)", functionalSymbol, Util.join(", ", arguments));
    }
}
