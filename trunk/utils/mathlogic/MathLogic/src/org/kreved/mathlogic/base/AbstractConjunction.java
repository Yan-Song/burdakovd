package org.kreved.mathlogic.base;

import java.util.Collection;
import java.util.Collections;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

import org.kreved.mathlogic.util.CommonUtils;
import org.kreved.mathlogic.util.Function;
import org.kreved.mathlogic.util.Functional;

/**
 * @param <O>
 *            тип аргументов конъюнкции
 * @param <S>
 *            тип результата применения подстановки к этой формуле
 * @author burdakovd
 * 
 */
public abstract class AbstractConjunction<O extends Formula<? extends O>, S extends Formula<? extends S>>
        extends AbstractPrimitiveOperator<O, S> {

    /**
     * 
     */
    private static final int PRIORITY = 4;

    /**
     * @param operands
     *            операнды конъюнкции
     */
    public AbstractConjunction(final Collection<? extends O> operands) {
        super("&", operands);
    }

    @Override
    public final Set<SemanticTable> applyTableDeductionLeft(
            final Iterator<Constant> constantProvider, final Iterator<? extends Term> terms) {

        return CommonUtils.singleElementSet(new SemanticTable(getOperands(), Collections
                .<Formula<?>> emptySet()));
    }

    @Override
    public final Set<SemanticTable> applyTableDeductionRight(
            final Iterator<Constant> constantProvider, final Iterator<? extends Term> terms) {

        return Collections.unmodifiableSet(new HashSet<SemanticTable>(Functional.mapList(

        getOperands(),

        new Function<O, SemanticTable>() {

            @Override
            public SemanticTable apply(final O operand) {
                return new SemanticTable(Collections.<Formula<?>> emptySet(), CommonUtils
                        .singleElementSet(operand));
            }
        }

        )));
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
