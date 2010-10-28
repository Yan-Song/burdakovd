package org.kreved.mathlogic.base;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;
import java.util.Set;

import org.kreved.mathlogic.util.Function;
import org.kreved.mathlogic.util.Functional;
import org.kreved.mathlogic.util.MathUtil;
import org.kreved.mathlogic.util.Predicate;

/**
 * Формула, полученная применением некоторого бинарного оператора к набору
 * операндов определенного типа.
 * <p>
 * Если обозначить оператор за <code>+</code>, то это формула вида
 * <code>op1 + op2 + ... + opn</code>
 * 
 * @param <O>
 *            тип операндов
 * @param <S>
 *            тип результата применения подстановки к этой формуле
 * @author burdakovd
 * 
 */
public abstract class AbstractMultiOperandOperatorApplication<O extends Formula<? extends O>, S extends Formula<?>>
        extends AbstractCompoundFormula<S> {

    /**
     * Строковое представление оператора.
     * <p>
     * Используется для преобразования формулы в строку, для вычисления хэша и
     * для сравнения формул.
     */
    private final String operation;

    /**
     * Набор операндов.
     */
    private final List<O> operands;

    /**
     * @param operation
     *            строковое представление оператора
     * @param operands
     *            набор операндов
     */
    public AbstractMultiOperandOperatorApplication(final String operation,
            final Collection<? extends O> operands) {

        this.operation = operation;
        this.operands = Collections.unmodifiableList(new ArrayList<O>(operands));
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.Substitutable#applySubstitution(org.kreved.
     * mathlogic.base.Substitution)
     */
    @Override
    public final S applySubstitution(final Substitution substitution) {

        return create(Functional.mapList(operands, new Function<O, O>() {
            @Override
            public O apply(final O argument) {
                return argument.applySubstitution(substitution);
            }
        }));
    }

    /**
     * @param operand
     *            один из операндов
     * 
     * @return строковое представление этого операнда, если нужно, окруженное
     *         скобками
     */
    private String bracesIfNeeded(final O operand) {
        return neededBraces(operand) ? "(" + operand + ")" : operand.toString();
    }

    /**
     * Этот метод используется в {@link AbstractMultiOperandOperatorApplication}
     * для применения подстановок.
     * 
     * @param operands
     *            операнды
     * @return формулу с заданными операндами и с той же операцией, что и
     *         текущая формула
     */
    protected abstract S create(List<O> operands);

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
        final AbstractMultiOperandOperatorApplication<?, ?> other =
                (AbstractMultiOperandOperatorApplication<?, ?>) obj;
        if (operands == null) {
            if (other.operands != null) {
                return false;
            }
        } else if (!operands.equals(other.operands)) {
            return false;
        }
        if (operation == null) {
            if (other.operation != null) {
                return false;
            }
        } else if (!operation.equals(other.operation)) {
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
        return MathUtil.union(Functional.map(operands, new Function<O, Set<Constant>>() {
            @Override
            public Set<Constant> apply(final O argument) {
                return argument.getConstants();
            }
        }));
    }

    /*
     * (non-Javadoc)
     * 
     * @see org.kreved.mathlogic.base.Formula#getFreeVariables()
     */
    @Override
    public final Set<Variable> getFreeVariables() {
        return MathUtil.union(Functional.map(operands, new Function<O, Set<Variable>>() {
            @Override
            public Set<Variable> apply(final O argument) {
                return argument.getFreeVariables();
            }
        }));
    }

    /**
     * @return the operands
     */
    public final List<O> getOperands() {
        return operands;
    }

    /**
     * @return the operation
     */
    public final String getOperation() {
        return operation;
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
        result = prime * result + (operands == null ? 0 : operands.hashCode());
        result = prime * result + (operation == null ? 0 : operation.hashCode());
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
        // переменная будет свободна тогда и только тогда, когда она свободна во
        // всех операндах
        return Functional.all(new Predicate<O>() {
            @Override
            public boolean apply(final O operand) {
                return operand.isVariableFreeForTerm(variable, term);
            }
        }, operands);
    }

    /**
     * @param operand
     *            один из операндов формулы
     * @return нужны ли скобки вокруг него
     */
    protected abstract boolean neededBraces(O operand);

    @Override
    public final String toString() {

        return MathUtil.join(

        String.format(" %s ", operation),

        Functional.map(operands, new Function<O, String>() {
            @Override
            public String apply(final O operand) {
                return bracesIfNeeded(operand);
            }
        })

        );
    }

}
