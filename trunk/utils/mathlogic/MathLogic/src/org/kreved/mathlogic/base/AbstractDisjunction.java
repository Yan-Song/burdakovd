package org.kreved.mathlogic.base;

import java.util.Collection;
import java.util.Collections;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

import org.kreved.mathlogic.util.CommonUtils;
import org.kreved.mathlogic.util.Function;
import org.kreved.mathlogic.util.Functional;

/**
 * @param <S>
 *            тип результата применения подстановки к этой формуле
 * @param <O>
 *            тип операндов дизъюнкции
 * @author burdakovd
 * 
 */
public abstract class AbstractDisjunction<O extends Formula<? extends O>, S extends Formula<? extends S>>
        extends AbstractPrimitiveOperator<O, S> {

    /**
     * 
     */
    private static final int PRIORITY = 3;

    /**
     * @param operands
     *            набор операндов
     */
    public AbstractDisjunction(final Collection<? extends O> operands) {
        super("V", operands);
    }

    @Override
    public final Set<SemanticTable> applyTableDeductionLeft(
            final Iterator<Constant> constantProvider, final Iterator<? extends Term> terms) {

        return Collections.unmodifiableSet(new HashSet<SemanticTable>(Functional.mapList(

        getOperands(),

        new Function<O, SemanticTable>() {

            @Override
            public SemanticTable apply(final O argument) {
                return new SemanticTable(CommonUtils.singleElementSet(argument), Collections
                        .<Formula<?>> emptySet());
            }
        })));
    }

    @Override
    public final Set<SemanticTable> applyTableDeductionRight(
            final Iterator<Constant> constantProvider, final Iterator<? extends Term> terms) {

        return CommonUtils.singleElementSet(new SemanticTable(Collections.<Formula<?>> emptySet(),
                getOperands()));
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.AbstractPrimitiveOperator#createNegatedPrimitive
     * (java.util.List)
     */
    @Override
    protected final PrimitiveFormula<?> createNegatedPrimitive(
            final List<PrimitiveFormula<?>> primitiveOperands) {
        return new ConjunctionOfPrimitives<PrimitiveFormula<?>>(primitiveOperands);
    }

    @Override
    protected final PrimitiveFormula<?> createPrimitive(final List<PrimitiveFormula<?>> operands) {
        return new DisjunctionOfPrimitives<PrimitiveFormula<?>>(operands);
    }

    /*
     * (non-Javadoc)
     * 
     * @see org.kreved.mathlogic.base.Formula#getPriority()
     */
    @Override
    public final int getPriority() {
        return PRIORITY;
    }

}
