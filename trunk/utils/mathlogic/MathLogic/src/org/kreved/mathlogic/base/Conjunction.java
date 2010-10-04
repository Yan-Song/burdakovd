package org.kreved.mathlogic.base;

import java.util.Collections;
import java.util.Iterator;
import java.util.Set;

import org.kreved.mathlogic.util.MathUtil;

/**
 * @author burdakovd
 * 
 */
public final class Conjunction extends AbstractBinaryAssociativeFormula {

    /**
     * 
     */
    private static final int PRIORITY = 4;

    /**
     * Создаёт формулу "left и right".
     * 
     * @param left
     *            левая часть
     * @param right
     *            правая часть
     */
    public Conjunction(final Formula left, final Formula right) {
        super("&", left, right);
    }

    @Override
    public Set<SemanticTable> applyTableDeductionLeft(final Iterator<Constant> constantProvider,
            final Iterable<? extends Term> terms) {
        return MathUtil.unmodifiableSet(new SemanticTable(MathUtil.unmodifiableSet(getLeft(),
                getRight()), Collections.<Formula> emptySet()));
    }

    @Override
    public Set<SemanticTable> applyTableDeductionRight(final Iterator<Constant> constantProvider,
            final Iterable<? extends Term> terms) {

        return MathUtil.unmodifiableSet(

        new SemanticTable(Collections.<Formula> emptySet(), MathUtil.unmodifiableSet(getLeft())),

        new SemanticTable(Collections.<Formula> emptySet(), MathUtil.unmodifiableSet(getRight()))

        );
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
        return new Conjunction(left, right);
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
