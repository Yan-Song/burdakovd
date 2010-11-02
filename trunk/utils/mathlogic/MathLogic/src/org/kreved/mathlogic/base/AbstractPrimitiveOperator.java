package org.kreved.mathlogic.base;

import java.util.AbstractMap.SimpleEntry;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Map.Entry;

import org.kreved.mathlogic.util.CommonUtils;

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
     * @param primitiveOperands
     *            операнды
     * @return формулу с заданными операндами, и с оператором, который был бы
     *         получен в результате прохождения оператора текущей формулы через
     *         отрицание
     */
    protected abstract PrimitiveFormula<?> createNegatedPrimitive(
            List<PrimitiveFormula<?>> primitiveOperands);

    /**
     * @param operands
     *            набор операндов
     * @return формулу с тем же оператором, но с заданными операндами
     */
    protected abstract PrimitiveFormula<?>
            createPrimitive(final List<PrimitiveFormula<?>> operands);

    @Override
    public final Entry<Collection<Entry<Quantor, Variable>>, PrimitiveFormula<?>> toPrimitive(
            final boolean needNegate) {

        final List<PrimitiveFormula<?>> primitiveOperands = new ArrayList<PrimitiveFormula<?>>();
        final List<Collection<Entry<Quantor, Variable>>> prefixes =
                new ArrayList<Collection<Entry<Quantor, Variable>>>();

        for (final O operand : getOperands()) {
            final Entry<Collection<Entry<Quantor, Variable>>, PrimitiveFormula<?>> entry =
                    operand.toPrimitive(needNegate);
            primitiveOperands.add(entry.getValue());
            prefixes.add(entry.getKey());
        }

        return new SimpleEntry<Collection<Entry<Quantor, Variable>>, PrimitiveFormula<?>>(
                CommonUtils.concatenate(prefixes),
                needNegate ? createNegatedPrimitive(primitiveOperands)
                        : createPrimitive(primitiveOperands));
    }
}
