package org.kreved.mathlogic.base;

import java.util.Collection;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * @param <O>
 *            тип аргументов конъюнкции
 * @author burdakovd
 * 
 */
public final class ConjunctionOfPrimitives<O extends PrimitiveFormula<? extends O>> extends
        AbstractConjunction<O, ConjunctionOfPrimitives<O>> implements
        PrimitiveFormula<ConjunctionOfPrimitives<O>> {

    /**
     * @param operands
     *            операнды
     */
    public ConjunctionOfPrimitives(final Collection<? extends O> operands) {
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
    protected ConjunctionOfPrimitives<O> create(final List<O> operands) {
        return new ConjunctionOfPrimitives<O>(operands);
    }

    /*
     * (non-Javadoc)
     * 
     * @see org.kreved.mathlogic.base.PrimitiveFormula#makeCNF()
     */
    @Override
    public Conjunction<Disjunction<Litera<?>>> makeCNF() {
        // попутно устраним повторяющиеся дизъюнкты
        final Set<Disjunction<Litera<?>>> disjuncts = new HashSet<Disjunction<Litera<?>>>();

        for (final O operand : getOperands()) {
            disjuncts.addAll(operand.makeCNF().getOperands());
        }

        return new Conjunction<Disjunction<Litera<?>>>(disjuncts);
    }

}
