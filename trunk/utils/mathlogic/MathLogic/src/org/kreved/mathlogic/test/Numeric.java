package org.kreved.mathlogic.test;

import static org.junit.Assert.assertTrue;

import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import org.junit.Test;
import org.kreved.mathlogic.base.Constant;
import org.kreved.mathlogic.base.Formula;
import org.kreved.mathlogic.base.PrefixedConstantProvider;
import org.kreved.mathlogic.base.SemanticTable;
import org.kreved.mathlogic.util.MathUtil;
import org.kreved.mathlogic.util.Parser;
import org.kreved.mathlogic.util.Parser.FiniteMatcher;

/**
 * @author burdakovd
 * 
 */
public final class Numeric {

    /**
     * 
     */
    private static final FiniteMatcher EMPTY_MATCHER = new Parser.FiniteMatcher(
            Collections.<String> emptySet());
    /**
     * 
     */
    private final Set<Formula> base;

    /**
     * 
     */
    private final Collection<Constant> baseConstants;

    /**
     * 
     */
    public Numeric() {

        final List<String> knowledgeBase = Arrays.asList(

        "any x exists y next(y, x)",

        "any x (1(x) => !(exists y next(x, y)))",

        "any x (!1(x) => exists y next(x, y))"

        );

        base = new HashSet<Formula>();
        baseConstants = new HashSet<Constant>();

        for (final String formula : knowledgeBase) {
            final Formula parsed = Parser.parseFormula(formula, EMPTY_MATCHER);
            base.add(parsed);
            baseConstants.addAll(parsed.getConstants());
            assertTrue(parsed.getFreeVariables().isEmpty());
        }

    }

    /**
     * 
     * @param formula
     *            формула
     * @return является ли формула следствием базы знаний
     */
    @SuppressWarnings("unchecked")
    public boolean checkFormula(final String formula) {

        final Formula parsed = Parser.parseFormula(formula, EMPTY_MATCHER);
        assertTrue(parsed.getFreeVariables().isEmpty());

        final boolean ans =
                MathUtil.doTableDeduction(
                        new SemanticTable(base, MathUtil.unmodifiableSet(parsed)),
                        new PrefixedConstantProvider("c", MathUtil.mergeWithMakingUnique(
                                parsed.getConstants(), baseConstants)));

        System.out.println(parsed + " == " + ans);

        return ans;
    }

    /**
     * 
     */
    @Test
    public void commonTest() {
        checkFormula("any x (1(x) => !next(x, x))");

        System.out.flush();
    }
}
