package org.kreved.mathlogic.base;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import java.util.Arrays;

import org.junit.Test;
import org.kreved.mathlogic.util.Util;

/**
 * @author burdakovd
 * 
 */
public final class CommonTest {

    /**
     * 
     */
    @Test
    public void formulaGetVariables() {

        final Formula formula =
                new ExistsSuch(new Variable("x2"), new Implication(new ForAny(new Variable("x1"),
                        new Negation(new AtomicFormula(new PredicateSymbol("R"),
                                Arrays.asList(new Variable("x1"))))), new AtomicFormula(
                        new PredicateSymbol("P"), Arrays.asList(
                                new Variable("x1"),
                                new CompoundTerm(new FunctionalSymbol("f"), Arrays.asList(
                                        new Constant("c"), new Variable("x2")))))));

        assertEquals(Util.unmodifiableSet(new Variable("x1")), formula.getFreeVariables());

    }

    /**
     * 
     */
    @Test
    public void formulaSubstitution() {

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
