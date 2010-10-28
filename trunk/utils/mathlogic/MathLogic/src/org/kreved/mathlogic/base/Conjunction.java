package org.kreved.mathlogic.base;

import java.util.Collection;
import java.util.Collections;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

import org.kreved.mathlogic.util.Function;
import org.kreved.mathlogic.util.Functional;
import org.kreved.mathlogic.util.MathUtil;

/**
 * @param <O>
 *            тип аргументов конъюнкции
 * @author burdakovd
 * 
 */
public final class Conjunction<O extends Formula<? extends O>> extends
        AbstractAssociativeOperator<O, Conjunction<O>> {

    /**
     * 
     */
    private static final int PRIORITY = 4;

    /**
     * @param operands
     *            операнды конъюнкции
     */
    public Conjunction(final Collection<? extends O> operands) {
        super("&", operands);
    }

    @Override
    public Set<SemanticTable> applyTableDeductionLeft(final Iterator<Constant> constantProvider,
            final Iterable<? extends Term> terms) {

        return MathUtil.singleElementSet(new SemanticTable(getOperands(), Collections
                .<Formula<?>> emptySet()));
    }

    @Override
    public Set<SemanticTable> applyTableDeductionRight(final Iterator<Constant> constantProvider,
            final Iterable<? extends Term> terms) {

        return Collections.unmodifiableSet(new HashSet<SemanticTable>(Functional.mapList(

        getOperands(),

        new Function<O, SemanticTable>() {

            @Override
            public SemanticTable apply(final O operand) {
                return new SemanticTable(Collections.<Formula<?>> emptySet(), MathUtil
                        .singleElementSet(operand));
            }
        }

        )));
    }

    @Override
    protected Conjunction<O> create(final List<O> operands) {
        return new Conjunction<O>(operands);
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
