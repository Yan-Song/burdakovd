package org.kreved.mathlogic.base;

import java.util.Collection;
import java.util.Collections;
import java.util.Iterator;
import java.util.Map.Entry;
import java.util.Set;

import org.kreved.mathlogic.util.CommonUtils;
import org.kreved.mathlogic.util.Of;

/**
 * @param <L>
 *            тип посылки
 * @param <R>
 *            тип следствия
 * @author burdakovd
 * 
 */
public final class Implication<L extends Formula<? extends L>, R extends Formula<? extends R>>
        extends AbstractBinaryFormula<L, R, Implication<L, R>> {

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
            final Iterator<? extends Term> terms) {

        return CommonUtils.unmodifiableSet(Of.of(

                new SemanticTable(CommonUtils.singleElementSet(getRight()), Collections
                        .<Formula<?>> emptySet()),

                new SemanticTable(Collections.<Formula<?>> emptySet(), CommonUtils
                        .singleElementSet(getLeft()))

        ));
    }

    @Override
    public Set<SemanticTable> applyTableDeductionRight(final Iterator<Constant> constantProvider,
            final Iterator<? extends Term> terms) {

        return CommonUtils.singleElementSet(new SemanticTable(CommonUtils
                .singleElementSet(getLeft()), CommonUtils.singleElementSet(getRight())));
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.AbstractBinaryFormula#create(org.kreved.mathlogic
     * .base.Formula, org.kreved.mathlogic.base.Formula)
     */
    @Override
    protected Implication<L, R> create(final L left, final R right) {
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

    /*
     * (non-Javadoc)
     * 
     * @see org.kreved.mathlogic.base.Formula#toPrimitive()
     */
    @Override
    public Entry<Collection<Entry<Quantor, Variable>>, PrimitiveFormula<?>> toPrimitive(
            final boolean needNegate) {
        // A => B == !A V B
        final Negation<L> first = new Negation<L>(getLeft());
        final R second = getRight();
        return new Disjunction<Formula<?>>(Of.of(first, second)).toPrimitive(needNegate);
    }

}
