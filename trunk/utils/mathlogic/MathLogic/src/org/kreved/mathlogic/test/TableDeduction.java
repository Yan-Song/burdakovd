package org.kreved.mathlogic.test;

import static org.junit.Assert.assertTrue;

import java.util.Collections;

import org.junit.Test;
import org.kreved.mathlogic.base.Formula;
import org.kreved.mathlogic.base.PrefixedConstantProvider;
import org.kreved.mathlogic.base.SemanticTable;
import org.kreved.mathlogic.util.CommonUtils;
import org.kreved.mathlogic.util.Parser;
import org.kreved.mathlogic.util.Parser.ConstantMatcher;

/**
 * @author burdakovd
 * 
 */
public final class TableDeduction {

    /**
     * 
     */
    public static final ConstantMatcher DIGITAL_CONSTANT_MATCHER = new ConstantMatcher() {
        @Override
        public boolean isConstant(final String name) {
            for (final char c : name.toCharArray()) {
                if (!Character.isDigit(c)) {
                    return false;
                }
            }
            return true;
        }
    };

    /**
     * 
     */
    @Test
    public void main() {

        final String[] trueFormulasToProve = new String[] {

        "P(x) => P(x)",

        "exists x P(x) => ! any x !P(x)",

        "any x P(x) => any y P(y)",

        "! exists x P(x) -> any x !P(x)",

        "! exists x P(x) -> any x !P(x)",

        "any x !P(x) -> ! exists x P(x)",

        "any x (P(x) & R(x)) -> (any x P(x) & any x R(x))",

        "(any x P(x) & any x R(x)) -> any x (P(x) & R(x))",

        "exists x (P(x) || R(x)) -> (exists x P(x) || exists x R(x))",

        "(exists x P(x) || exists x R(x)) -> exists x (P(x) || R(x))"

        };

        for (final String formula : trueFormulasToProve) {
            assertTrue(formula, prove(formula));
        }
    }

    /**
     * Доказать формулу.
     * 
     * @param formula
     *            формула
     * @return <code>true</code>, если удалось вывести, <code>false</code>, если
     *         удалось найти контрпример, или зациклиться
     */
    public boolean prove(final Formula<?> formula) {

        System.out.println("\nПытаемся доказать формулу " + formula);

        return org.kreved.mathlogic.util.TableDeduction.doTableDeduction(new SemanticTable(
                Collections.<Formula<?>> emptySet(), CommonUtils.singleElementSet(formula)),
                new PrefixedConstantProvider("c", formula.getConstants()));
    }

    /**
     * 
     * @param text
     *            текст формулы
     * @return общезначима ли формула
     */
    public boolean prove(final String text) {
        return prove(Parser.parseFormula(text, DIGITAL_CONSTANT_MATCHER));
    }

}
