package org.kreved.mathlogic.base;

import java.util.Collections;
import java.util.HashSet;
import java.util.Set;

/**
 * Содержит методы, общие для всех бинарных формул.
 * 
 * @author burdakovd
 * 
 */
public abstract class AbstractBinaryFormula implements Formula {

    /**
     * Строковое представление внешней бинарной операции этой формулы.
     * <p>
     * Используется для преобразования формулы в строку, для вычисления хэша и
     * для сравнения формул.
     */
    private final String operation;

    /**
     * Левая часть формулы.
     */
    private final Formula left;

    /**
     * Правая часть формулы.
     */
    private final Formula right;

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
    public AbstractBinaryFormula(final String operation, final Formula left, final Formula right) {
        this.operation = operation;
        this.left = left;
        this.right = right;
    }

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
        if (!(obj instanceof AbstractBinaryFormula)) {
            return false;
        }
        final AbstractBinaryFormula other = (AbstractBinaryFormula) obj;
        if (left == null) {
            if (other.left != null) {
                return false;
            }
        } else if (!left.equals(other.left)) {
            return false;
        }
        if (operation == null) {
            if (other.operation != null) {
                return false;
            }
        } else if (!operation.equals(other.operation)) {
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
    public final Formula getLeft() {
        return left;
    }

    /**
     * @return the operation
     */
    public final String getOperation() {
        return operation;
    }

    /**
     * @return the right
     */
    public final Formula getRight() {
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
        result = prime * result + (operation == null ? 0 : operation.hashCode());
        result = prime * result + (right == null ? 0 : right.hashCode());
        return result;
    }

    /*
     * (non-Javadoc)
     * 
     * @see java.lang.Object#toString()
     */
    @Override
    public final String toString() {
        return String.format("(%s %s %s)", left, operation, right);
    }
}
