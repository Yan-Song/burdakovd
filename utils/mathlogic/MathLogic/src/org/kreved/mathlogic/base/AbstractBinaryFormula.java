package org.kreved.mathlogic.base;

import java.util.Collections;
import java.util.HashSet;
import java.util.Set;

import org.kreved.mathlogic.util.CommonUtils;
import org.kreved.mathlogic.util.Function;

/**
 * Содержит методы, общие для всех бинарных формул.
 * 
 * @param <L>
 *            тип левой части формулы
 * @param <R>
 *            тип правой части формулы
 * @param <S>
 *            тип результата применения подстановки к этой формуле
 * @author burdakovd
 * 
 */
public abstract class AbstractBinaryFormula<L extends Formula<? extends L>, R extends Formula<? extends R>, S extends Formula<?>>
        extends AbstractCompoundFormula<S> {

    /**
     * Левая часть формулы.
     */
    private final L left;

    /**
     * Правая часть формулы.
     */
    private final R right;

    /**
     * @param operation
     *            Строковое представление внешней бинарной операции этой
     *            формулы. Используется для преобразования формулы в строку, для
     *            вычисления хэша и для сравнения формул.
     * @param left
     *            левая часть формулы
     * @param right
     *            правая часть формулы
     */
    public AbstractBinaryFormula(final String operation, final L left, final R right) {
        super(operation);
        this.left = left;
        this.right = right;
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
        return create(left.applySubstitution(substitution), right.applySubstitution(substitution));
    }

    /**
     * @param part
     *            часть формулы (левая или правая)
     * @return строковое представление этой части, если нужно, окруженное
     *         скобками
     */
    private String bracesIfNeeded(final Formula<?> part) {
        return neededBraces(part) ? "(" + part + ")" : part.toString();
    }

    /**
     * Этот метод используется в {@link AbstractBinaryFormula} для применения
     * подстановок.
     * 
     * @param left
     *            левая часть формулы
     * @param right
     *            правая часть
     * @return формулу с заданными левой и правой частью и с той же операцией,
     *         что и текущая формула
     */
    protected abstract S create(L left, R right);

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
        final AbstractBinaryFormula<?, ?, ?> other = (AbstractBinaryFormula<?, ?, ?>) obj;
        if (left == null) {
            if (other.left != null) {
                return false;
            }
        } else if (!left.equals(other.left)) {
            return false;
        }
        if (symbol() == null) {
            if (other.symbol() != null) {
                return false;
            }
        } else if (!symbol().equals(other.symbol())) {
            return false;
        }
        if (right == null) {
            if (other.right != null) {
                return false;
            }
        } else if (!right.equals(other.right)) {
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
        return CommonUtils.union(getLeft().getConstants(), getRight().getConstants());
    }

    /*
     * (non-Javadoc)
     * 
     * @see org.kreved.mathlogic.base.Formula#freeVariables()
     */
    @Override
    public final Set<Variable> getFreeVariables() {
        final Set<Variable> ans = new HashSet<Variable>(left.getFreeVariables());
        ans.addAll(right.getFreeVariables());
        return Collections.unmodifiableSet(ans);
    }

    /**
     * @return the left
     */
    public final L getLeft() {
        return left;
    }

    /**
     * @return the right
     */
    public final R getRight() {
        return right;
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
        result = prime * result + (left == null ? 0 : left.hashCode());
        result = prime * result + (symbol() == null ? 0 : symbol().hashCode());
        result = prime * result + (right == null ? 0 : right.hashCode());
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

        // переменная будет свободна тогда и только тогда, когда она свободна в
        // обоих частях формулы
        return left.isVariableFreeForTerm(variable, term)
                && right.isVariableFreeForTerm(variable, term);
    }

    /**
     * @param part
     *            часть формулы (левая или правая)
     * @return нужны ли скобки вокруг неё
     */
    protected abstract boolean neededBraces(Formula<?> part);

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.Formula#renameVariables(org.kreved.mathlogic
     * .util.Function)
     */
    @Override
    public final S renameVariables(final Function<? super Variable, ? extends Variable> renamer) {
        return create(getLeft().renameVariables(renamer), getRight().renameVariables(renamer));
    }

    @Override
    public final String toString() {
        return String.format("%s %s %s", bracesIfNeeded(getLeft()), symbol(),
                bracesIfNeeded(getRight()));
    }

}
