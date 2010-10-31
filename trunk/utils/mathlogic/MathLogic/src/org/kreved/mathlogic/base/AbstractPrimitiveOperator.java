package org.kreved.mathlogic.base;

import java.util.Collection;
import java.util.List;

import org.kreved.mathlogic.util.Function;
import org.kreved.mathlogic.util.Functional;

/**
 * Конъюнкция или дизъюнкция.
 * 
 * @param <O>
 *            тип операндов
 * @param <S>
 *            тип результата применения подстановки к этой формуле
 * @author burdakovd
 * 
 */
public abstract class AbstractPrimitiveOperator<O extends Formula<? extends O>, S extends Formula<? extends S>>
        extends AbstractAssociativeOperator<O, S> {

    /**
     * @param operation
     *            строковое представление оператора
     * @param operands
     *            набор операндов
     */
    public AbstractPrimitiveOperator(final String operation, final Collection<? extends O> operands) {
        super(operation, operands);
    }

    /**
     * @param operands
     *            набор операндов
     * @return формулу с тем же оператором, но с заданными операндами
     */
    protected abstract PrimitiveFormula<?>
            createPrimitive(final List<PrimitiveFormula<?>> operands);

    @Override
    public final PrimitiveFormula<?> toPrimitive() {
        return createPrimitive(Functional.mapList(getOperands(),
                new Function<Formula<?>, PrimitiveFormula<?>>() {

                    @Override
                    public PrimitiveFormula<?> apply(final Formula<?> argument) {
                        return argument.toPrimitive();
                    }
                }));
    }

}
