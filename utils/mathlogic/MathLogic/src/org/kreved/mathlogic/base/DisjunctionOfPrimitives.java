package org.kreved.mathlogic.base;

import java.util.Collection;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import org.kreved.mathlogic.util.CommonUtils;
import org.kreved.mathlogic.util.Of;

/**
 * @param <O>
 *            тип аргументов дизъюнкции
 * @author burdakovd
 * 
 */
public final class DisjunctionOfPrimitives<O extends PrimitiveFormula<? extends O>> extends
        AbstractDisjunction<O, DisjunctionOfPrimitives<O>> implements
        PrimitiveFormula<DisjunctionOfPrimitives<O>> {

    /**
     * @param operands
     *            операнды
     */
    public DisjunctionOfPrimitives(final Collection<? extends O> operands) {
        super(operands);
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.kreved.mathlogic.base.AbstractMultiOperandOperatorApplication#create
     * (java.util.List)
     */
    @Override
    protected DisjunctionOfPrimitives<O> create(final List<O> operands) {
        return new DisjunctionOfPrimitives<O>(operands);
    }

    /*
     * (non-Javadoc)
     * 
     * @see org.kreved.mathlogic.base.PrimitiveFormula#makeCNF()
     */
    @Override
    public Conjunction<Disjunction<Litera<?>>> makeCNF() {

        // изначально берём один пустой дизъюнкт
        // используем Set, устраняя повторы
        Set<Disjunction<Litera<?>>> disjuncts =
                new HashSet<Disjunction<Litera<?>>>(Of.of(new Disjunction<Litera<?>>(Collections
                        .<Litera<?>> emptySet())));

        for (final O operand : getOperands()) {
            final Set<Disjunction<Litera<?>>> newDisjuncts = new HashSet<Disjunction<Litera<?>>>();

            for (final Disjunction<Litera<?>> rightDisjunct : operand.makeCNF().getOperands()) {
                for (final Disjunction<Litera<?>> leftDisjunct : disjuncts) {
                    // union возвращает Set, так что устранит повторы
                    newDisjuncts.add(new Disjunction<Litera<?>>(CommonUtils.union(
                            leftDisjunct.getOperands(), rightDisjunct.getOperands())));
                }
            }

            disjuncts = newDisjuncts;
        }

        return new Conjunction<Disjunction<Litera<?>>>(disjuncts);
    }

}
