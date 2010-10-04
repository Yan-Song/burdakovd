package org.kreved.mathlogic.base;

import java.util.Set;

import org.kreved.mathlogic.util.MathUtil;

/**
 * @author burdakovd
 * 
 */
public abstract class AbstractQuantifiedFormula extends AbstractCompoundFormula {

    /**
     * 
     */
    private static final int PRIORITY = 5;

    /**
     * Строковое представление квантора. Используется для hashCode, equals,
     * toString
     */
    private final String quantor;

    /**
     * Переменная, связуемая квантором.
     */
    private final Variable variable;

    /**
     * Формула, к которой прменяется квантор.
     */
    private final Formula formula;

    /**
     * @param quantor
     *            Строковое представление квантора. Используется для hashCode,
     *            equals, toString
     * @param variable
     *            Переменная, связуемая квантором.
     * @param formula
     *            Формула, к которой прменяется квантор.
     */
    public AbstractQuantifiedFormula(final String quantor, final Variable variable,
            final Formula formula) {

        this.quantor = quantor;
        this.variable = variable;
        this.formula = formula;
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.Substitutable#applySubstitution(org.kreved.
     * mathlogic.base.Substitution)
     */
    @Override
    public final Formula applySubstitution(final Substitution substitution) {

        // применяем подстановку ко всем переменным, кроме связанной квантором

        final Substitution modifiedSubstitution = new Substitution() {
            @Override
            public Term apply(final Variable variable) {
                return variable.equals(AbstractQuantifiedFormula.this.variable) ? variable
                        : substitution.apply(variable);
            }

            @Override
            public boolean isCorrectFor(final Formula formula) {
                throw new UnsupportedOperationException();
            }

        };

        final Formula substitutedFormula = formula.applySubstitution(modifiedSubstitution);

        return create(variable, substitutedFormula);
    }

    /**
     * Используется {@link AbstractQuantifiedFormula} для применения
     * подстановок.
     * 
     * @param variable
     *            переменная, связуемая квантором
     * @param formula
     *            формула, к которой применяется квантор
     * @return новая формула с тем же квантором, но с заданной переменной и
     *         формулой к которой квантор будет применяться
     */
    protected abstract Formula create(Variable variable, Formula formula);

    /*
     * (non-Javadoc)
     * 
     * @see java.lang.Object#equals(java.lang.Object)
     */
    @Override
    public final boolean equals(final Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final AbstractQuantifiedFormula other = (AbstractQuantifiedFormula) obj;
        if (formula == null) {
            if (other.formula != null) {
                return false;
            }
        } else if (!formula.equals(other.formula)) {
            return false;
        }
        if (quantor == null) {
            if (other.quantor != null) {
                return false;
            }
        } else if (!quantor.equals(other.quantor)) {
            return false;
        }
        if (variable == null) {
            if (other.variable != null) {
                return false;
            }
        } else if (!variable.equals(other.variable)) {
            return false;
        }
        return true;
    }

    /*
     * (non-Javadoc)
     * 
     * @see org.kreved.mathlogic.base.Formula#getConstants()
     */
    @Override
    public final Set<Constant> getConstants() {
        return formula.getConstants();
    }

    /**
     * @return the formula
     */
    public final Formula getFormula() {
        return formula;
    }

    /*
     * (non-Javadoc)
     * 
     * @see org.kreved.mathlogic.base.Formula#freeVariables()
     */
    @Override
    public final Set<Variable> getFreeVariables() {
        return MathUtil.excluding(formula.getFreeVariables(), variable);
    }

    @Override
    public final int getPriority() {
        return PRIORITY;
    }

    /**
     * @return the quantor
     */
    public final String getQuantor() {
        return quantor;
    }

    /**
     * @return the variable
     */
    public final Variable getVariable() {
        return variable;
    }

    /*
     * (non-Javadoc)
     * 
     * @see java.lang.Object#hashCode()
     */
    @Override
    public final int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + (formula == null ? 0 : formula.hashCode());
        result = prime * result + (quantor == null ? 0 : quantor.hashCode());
        result = prime * result + (variable == null ? 0 : variable.hashCode());
        return result;
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.Formula#isVariableFreeForTerm(org.kreved.mathlogic
     * .base.Variable, org.kreved.mathlogic.base.Term)
     */
    @Override
    public final boolean isVariableFreeForTerm(final Variable variable, final Term term) {

        if (variable.equals(this.variable)) {

            // эта переменная связывается, внутри свободных её вхождений не
            // будет
            return true;

        } else if (term.getVariables().contains(this.variable)) {

            // этот квантор связывает одну из переменных, используемых термом
            // значит подставлять его внутри формулы нельзя
            // значит внутренняя формула не должна содержать свободных вхождений
            // переменной, которую предстоит заменить
            return !formula.getFreeVariables().contains(variable);

        } else {

            // этот квантор не связывает ни заменяемую переменную, ни какую-либо
            // из переменных терма
            // значит этот квантор ни на что не влияет
            return formula.isVariableFreeForTerm(variable, term);
        }
    }

    @Override
    public final String toString() {
        return String.format(getFormula().getPriority() >= getPriority() ? "%s %s %s"
                : "%s %s (%s)", getQuantor(), getVariable(), getFormula());
    }
}
