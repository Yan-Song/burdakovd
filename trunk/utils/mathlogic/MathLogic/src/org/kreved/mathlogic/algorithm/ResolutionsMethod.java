package org.kreved.mathlogic.algorithm;

import java.util.List;
import java.util.Map.Entry;

import org.kreved.mathlogic.base.Formula;
import org.kreved.mathlogic.base.PNF;
import org.kreved.mathlogic.base.PrimitiveFormula;
import org.kreved.mathlogic.base.Quantor;
import org.kreved.mathlogic.base.Variable;

/**
 * Метод резолюций.
 * 
 * @author burdakovd
 * 
 */
public final class ResolutionsMethod {

    /**
     * 
     * @param formula
     *            исходная формула
     * @return ПНФ для этой формулы
     */
    public static PNF makePNF(final Formula<?> formula) {
        final Entry<? extends List<? extends Entry<Quantor, Variable>>, ? extends PrimitiveFormula<?>> entry =
                formula.toPrimitive(false);
        return new PNF(entry.getValue().makeCNF(), entry.getKey());
    }

    /**
     * Hide utility class ctor.
     */
    private ResolutionsMethod() {
    }
}
