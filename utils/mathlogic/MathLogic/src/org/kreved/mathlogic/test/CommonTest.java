package org.kreved.mathlogic.test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import java.util.Arrays;

import org.junit.Test;
import org.kreved.mathlogic.base.AtomicFormula;
import org.kreved.mathlogic.base.CompoundTerm;
import org.kreved.mathlogic.base.Constant;
import org.kreved.mathlogic.base.ExistsSuch;
import org.kreved.mathlogic.base.ForAny;
import org.kreved.mathlogic.base.Formula;
import org.kreved.mathlogic.base.FunctionalSymbol;
import org.kreved.mathlogic.base.Implication;
import org.kreved.mathlogic.base.Negation;
import org.kreved.mathlogic.base.PredicateSymbol;
import org.kreved.mathlogic.base.Variable;
import org.kreved.mathlogic.util.CommonUtils;
import org.kreved.mathlogic.util.Parser;

/**
 * @author burdakovd
 * 
 */
public final class CommonTest {

    /**
     * 
     */
    private static final Formula<?> BIG_FORMULA = new ExistsSuch<Formula<?>>(new Variable("x2"),
            new Implication<Formula<?>, Formula<?>>(new ForAny<Formula<?>>(new Variable("x1"),
                    new Negation<Formula<?>>(new AtomicFormula(new PredicateSymbol("R"),
                            Arrays.asList(new Variable("x1"))))), new AtomicFormula(
                    new PredicateSymbol("P"), Arrays.asList(
                            new Variable("x1"),
                            new CompoundTerm(new FunctionalSymbol("f"), Arrays.asList(new Constant(
                                    "c"), new Variable("x2")))))));

    /**
     * 
     */
    @Test
    public void formulaGetVariables() {

        assertEquals(CommonUtils.singleElementSet(new Variable("x1")), BIG_FORMULA.getFreeVariables());

    }

    /**
     * 
     */
    @Test
    public void formulaParsing() {

        final Formula<?> parsed = Parser.parseFormula(BIG_FORMULA.toString());
        assertEquals(BIG_FORMULA, parsed);

        for (final String stringFormula : Arrays.asList(

        "P(x1, f(c, x2))",

        "R(x1)",

        "(!R(x1))",

        "((any x1(!R(x1))) -> P(x1,f(c, x2)))",

        "(exists x2 ((any x1(!R(x1))) -> P(x1, f(c, x2))))"

        )) {
            final Formula<?> parsedFormula = Parser.parseFormula(stringFormula);
            final Formula<?> stage2 = Parser.parseFormula(stringFormula.toString());

            // проверяем, что разбор строкового представления формулы совпадёт с
            // исходной формулой
            assertEquals(parsedFormula, stage2);

            // дополнительная ручная проверка
            // System.out.println(String.format("'%s' parsed as '%s'",
            // stringFormula, parsedFormula));
        }

        // пример правильного восстановления скобок
        final String shortened =
                "any x1 !P(x1) & exists x2 R(x1, x2) -> exists x1 (!P(x1) || P(x2))";
        final String full =
                "(((any x1 (!P(x1))) & (exists x2 R(x1, x2))) -> (exists x1 ((!P(x1)) || P(x2))))";
        assertEquals(Parser.parseFormula(shortened), Parser.parseFormula(full));
        // System.out.println(String.format("'%s' shortened as '%s'", full,
        // Parser.parseFormula(full)
        // .toString()));
    }

    /**
     * 
     */
    @Test
    public void termGetVariables() {

        final CompoundTerm compoundTerm =
                new CompoundTerm(new FunctionalSymbol("f"), Arrays.asList(
                        new Constant("c1"),
                        new CompoundTerm(new FunctionalSymbol("g"), Arrays.asList(new CompoundTerm(
                                new FunctionalSymbol("h"), Arrays.asList(new Constant("c1"))),
                                new Constant("c2")))));

        assertTrue("это основной терм", compoundTerm.getVariables().isEmpty());
    }

    /**
     * Тест со слайдов.
     */
    @Test
    public void testVariableFreeForTerm() {

        final Formula<?> formula =
                Parser.parseFormula("any x (P(x) -> !R(y)) -> R(f(x)) || exists y P(y)");

        assertFalse(formula.isVariableFreeForTerm(new Variable("y"), Parser.parseTerm("f(x, z)")));
        assertTrue(formula.isVariableFreeForTerm(new Variable("y"), Parser.parseTerm("f(y, z)")));
    }
}
