package org.kreved.mathlogic.base;

import java.util.Collections;
import java.util.Iterator;
import java.util.Set;

import org.kreved.mathlogic.util.MathUtil;

/**
 * @param <L>
 *            тип посылки
 * @param <R>
 *            тип следствия
 * @author burdakovd
 * 
 */
public final class Implication<L extends Formula<? extends L>, R extends Formula<? extends R>>
        extends AbstractBinaryFormula<L, R> {

    /**
     * 
     */
    private static final int PRIORITY = 2;

    /**
     * Создаёт формулу "если left, то right".
     * 
     * @param left
     *            посылка
     * @param right
     *            следствие
     */
    public Implication(final L left, final R right) {
        super("->", left, right);
    }

    @Override
    public Set<SemanticTable> applyTableDeductionLeft(final Iterator<Constant> constantProvider,
            final Iterable<? extends Term> terms) {

        return MathUtil.unmodifiableSet(MathUtil.of(

                new SemanticTable(MathUtil.singleElementSet(getRight()), Collections
                        .<Formula<?>> emptySet()),

                new SemanticTable(Collections.<Formula<?>> emptySet(), MathUtil
                        .singleElementSet(getLeft()))

        ));
    }

    @Override
    public Set<SemanticTable> applyTableDeductionRight(final Iterator<Constant> constantProvider,
            final Iterable<? extends Term> terms) {

        return MathUtil.singleElementSet(new SemanticTable(MathUtil.singleElementSet(getLeft()),
                MathUtil.singleElementSet(getRight())));
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.AbstractBinaryFormula#create(org.kreved.mathlogic
     * .base.Formula, org.kreved.mathlogic.base.Formula)
     */
    @Override
    protected AbstractBinaryFormula<L, R> create(final L left, final R right) {
        return new Implication<L, R>(left, right);
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

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.AbstractBinaryFormula#neededBraces(org.kreved
     * .mathlogic.base.Formula)
     */
    @Override
    protected boolean neededBraces(final Formula<?> part) {
        return part.getPriority() <= getPriority();
    }

}
