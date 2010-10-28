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
 *            тип операндов дизъюнкции
 * @author burdakovd
 * 
 */
public final class Disjunction<O extends Formula<? extends O>> extends
        AbstractAssociativeOperator<O, Disjunction<O>> {

    /**
     * 
     */
    private static final int PRIORITY = 3;

    /**
     * @param operands
     *            набор операндов
     */
    public Disjunction(final Collection<? extends O> operands) {
        super("V", operands);
    }

    @Override
    public Set<SemanticTable> applyTableDeductionLeft(final Iterator<Constant> constantProvider,
            final Iterable<? extends Term> terms) {

        return Collections.unmodifiableSet(new HashSet<SemanticTable>(Functional.mapList(

        getOperands(),

        new Function<O, SemanticTable>() {

            @Override
            public SemanticTable apply(final O argument) {
                return new SemanticTable(MathUtil.singleElementSet(argument), Collections
                        .<Formula<?>> emptySet());
            }
        })));
    }

    @Override
    public Set<SemanticTable> applyTableDeductionRight(final Iterator<Constant> constantProvider,
            final Iterable<? extends Term> terms) {

        return MathUtil.singleElementSet(new SemanticTable(Collections.<Formula<?>> emptySet(),
                getOperands()));
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.AbstractMultiOperandOperatorApplication#create
     * (java.util.List)
     */
    @Override
    protected Disjunction<O> create(final List<O> operands) {
        return new Disjunction<O>(operands);
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
