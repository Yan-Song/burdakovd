package org.kreved.mathlogic.base;

import java.util.Collections;
import java.util.Iterator;
import java.util.Set;

import org.kreved.mathlogic.util.MathUtil;

/**
 * @author burdakovd
 * 
 */
public final class Disjunction extends AbstractBinaryAssociativeFormula {

    /**
     * 
     */
    private static final int PRIORITY = 3;

    /**
     * Создаёт формулу "left или right".
     * 
     * @param left
     *            левая часть дизъюнкции
     * @param right
     *            правая часть дизъюнкции
     */
    public Disjunction(final Formula left, final Formula right) {
        super("V", left, right);
    }

    @Override
    public Set<SemanticTable> applyTableDeductionLeft(final Iterator<Constant> constantProvider,
            final Iterable<? extends Term> terms) {

        return MathUtil.unmodifiableSet(

        new SemanticTable(MathUtil.unmodifiableSet(getLeft()), Collections.<Formula> emptySet()),

        new SemanticTable(MathUtil.unmodifiableSet(getRight()), Collections.<Formula> emptySet())

        );
    }

    @Override
    public Set<SemanticTable> applyTableDeductionRight(final Iterator<Constant> constantProvider,
            final Iterable<? extends Term> terms) {
        return MathUtil.unmodifiableSet(new SemanticTable(Collections.<Formula> emptySet(),
                MathUtil.unmodifiableSet(getLeft(), getRight())));
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.AbstractBinaryFormula#create(org.kreved.mathlogic
     * .base.Formula, org.kreved.mathlogic.base.Formula)
     */
    @Override
    protected Formula create(final Formula left, final Formula right) {
        return new Disjunction(left, right);
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

}
