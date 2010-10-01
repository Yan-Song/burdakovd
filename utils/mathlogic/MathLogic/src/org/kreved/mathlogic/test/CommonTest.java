package org.kreved.mathlogic.test;

import static org.junit.Assert.assertEquals;
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
import org.kreved.mathlogic.util.Parser;
import org.kreved.mathlogic.util.Util;

/**
 * @author burdakovd
 * 
 */
public final class CommonTest {

    /**
     * 
     */
    private static final ExistsSuch BIG_FORMULA = new ExistsSuch(new Variable("x2"),
            new Implication(new ForAny(new Variable("x1"), new Negation(new AtomicFormula(
                    new PredicateSymbol("R"), Arrays.asList(new Variable("x1"))))),
                    new AtomicFormula(new PredicateSymbol("P"), Arrays.asList(
                            new Variable("x1"),
                            new CompoundTerm(new FunctionalSymbol("f"), Arrays.asList(new Constant(
                                    "c"), new Variable("x2")))))));

    /**
     * 
     */
    @Test
    public void formulaGetVariables() {

        assertEquals(Util.unmodifiableSet(new Variable("x1")), BIG_FORMULA.getFreeVariables());

    }

    /**
     * 
     */
    @Test
    public void formulaParsing() {

        final Formula parsed = Parser.parseFormula(BIG_FORMULA.toString());
        assertEquals(BIG_FORMULA, parsed);

        for (final String stringFormula : Arrays.asList(

        "P(x1, f(c, x2))",

        "R(x1)",

        "(!R(x1))",

        "((any x1(!R(x1))) -> P(x1,f(c, x2)))",

        "(exists x2 ((any x1(!R(x1))) -> P(x1, f(c, x2))))"

        )) {
            final Formula parsedFormula = Parser.parseFormula(stringFormula);
            final Formula stage2 = Parser.parseFormula(stringFormula.toString());

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
}
