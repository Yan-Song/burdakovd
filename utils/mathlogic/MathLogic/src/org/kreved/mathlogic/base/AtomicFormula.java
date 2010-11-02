package org.kreved.mathlogic.base;

import java.util.AbstractMap.SimpleEntry;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map.Entry;
import java.util.Set;

import org.kreved.mathlogic.util.CommonUtils;
import org.kreved.mathlogic.util.Function;

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
public final class AtomicFormula implements Litera<AtomicFormula> {

    /**
     * 
     */
    private static final int PRIORITY = 7;

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
    public AtomicFormula(final PredicateSymbol predicateSymbol, final List<? extends Term> arguments) {
        this.predicateSymbol = predicateSymbol;
        this.arguments = Collections.unmodifiableList(new ArrayList<Term>(arguments));
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.Substitutable#applySubstitution(org.kreved.
     * mathlogic.base.Substitution)
     */
    @Override
    public AtomicFormula applySubstitution(final Substitution substitution) {

        final List<Term> substitutedArguments = new ArrayList<Term>();

        for (final Term argument : arguments) {
            substitutedArguments.add(argument.applySubstitution(substitution));
        }

        return new AtomicFormula(predicateSymbol, substitutedArguments);
    }

    @Override
    public Set<SemanticTable> applyTableDeductionLeft(final Iterator<Constant> constantProvider,
            final Iterator<? extends Term> terms) {

        return CommonUtils.singleElementSet(new SemanticTable(CommonUtils
                .<Formula<?>> singleElementSet(this), Collections.<Formula<?>> emptySet()));
    }

    @Override
    public Set<SemanticTable> applyTableDeductionRight(final Iterator<Constant> constantProvider,
            final Iterator<? extends Term> terms) {

        return CommonUtils.singleElementSet(new SemanticTable(Collections.<Formula<?>> emptySet(),
                CommonUtils.<Formula<?>> singleElementSet(this)));
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
     * @see org.kreved.mathlogic.base.Formula#getConstants()
     */
    @Override
    public Set<Constant> getConstants() {

        final Set<Constant> ans = new HashSet<Constant>();

        for (final Term term : arguments) {
            ans.addAll(term.getConstants());
        }

        return Collections.unmodifiableSet(ans);
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

    /*
     * (non-Javadoc)
     * 
     * @see org.kreved.mathlogic.base.Formula#getPriority()
     */
    @Override
    public int getPriority() {
        return PRIORITY;
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
     * @see org.kreved.mathlogic.base.Formula#isAtomic()
     */
    @Override
    public boolean isAtomic() {
        return true;
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.Formula#isVariableFreeForTerm(org.kreved.mathlogic
     * .base.Variable, org.kreved.mathlogic.base.Term)
     */
    @Override
    public boolean isVariableFreeForTerm(final Variable variable, final Term term) {
        return true;
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.Formula#renameVariables(org.kreved.mathlogic
     * .util.Function)
     */
    @Override
    public AtomicFormula renameVariables(final Function<Variable, Variable> renamer) {
        return this;
    }

    /*
     * (non-Javadoc)
     * 
     * @see org.kreved.mathlogic.base.Formula#symbol()
     */
    @Override
    public String symbol() {
        return "Atomic";
    }

    /*
     * (non-Javadoc)
     * 
     * @see org.kreved.mathlogic.base.Formula#toPrimitive()
     */
    @Override
    public Entry<Collection<Entry<Quantor, Variable>>, PrimitiveFormula<?>> toPrimitive(
            final boolean needNegate) {

        return new SimpleEntry<Collection<Entry<Quantor, Variable>>, PrimitiveFormula<?>>(
                Collections.<Entry<Quantor, Variable>> emptyList(), needNegate ? new NegatedAtom(
                        this) : this);
    }

    /*
     * (non-Javadoc)
     * 
     * @see java.lang.Object#toString()
     */
    @Override
    public String toString() {
        return String.format("%s(%s)", predicateSymbol, CommonUtils.join(", ", arguments));
    }
}
