package org.kreved.mathlogic.test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import java.util.AbstractMap.SimpleEntry;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map.Entry;
import java.util.Set;

import org.junit.Test;
import org.kreved.mathlogic.algorithm.BasicRenamer;
import org.kreved.mathlogic.base.AtomicFormula;
import org.kreved.mathlogic.base.Conjunction;
import org.kreved.mathlogic.base.Disjunction;
import org.kreved.mathlogic.base.ExistsSuch;
import org.kreved.mathlogic.base.ForAny;
import org.kreved.mathlogic.base.Formula;
import org.kreved.mathlogic.base.Litera;
import org.kreved.mathlogic.base.NegatedAtom;
import org.kreved.mathlogic.base.Negation;
import org.kreved.mathlogic.base.PNF;
import org.kreved.mathlogic.base.Quantor;
import org.kreved.mathlogic.base.Variable;
import org.kreved.mathlogic.util.Function;
import org.kreved.mathlogic.util.Functional;
import org.kreved.mathlogic.util.Of;
import org.kreved.mathlogic.util.Parser;

/**
 * @author burdakovd
 * 
 */
public final class ResolutionsMethod {

    /**
     * 
     */
    @Test
    public void convertToPrimitiveRemoveImplications() {
        final Formula<?> source = Parser.parseFormula("P(x) => Q(x)");
        final Formula<?> shouldBe = Parser.parseFormula("!P(x) V Q(x)");
        final Entry<? extends List<?>, ?> entry = source.toPrimitive(false);

        assertTrue(entry.getKey().isEmpty());
        assertEquals(shouldBe, entry.getValue());
    }

    /**
     * @param expected
     *            CNF, которую нужно получить
     * @param actual
     *            CNF, которая на самом деле
     * @return эквивалентны ли эти две формулы
     */
    private boolean equalCNF(final Formula<?> expected,
            final Conjunction<Disjunction<Litera<?>>> actual) {

        final Conjunction<?> expectedConjunction =
                expected instanceof Conjunction ? (Conjunction<?>) expected
                        : new Conjunction<Formula<?>>(Of.of(expected));
        final Set<Set<Litera<?>>> setsExpected = new HashSet<Set<Litera<?>>>();
        for (final Formula<?> disjunction : expectedConjunction.getOperands()) {
            final Disjunction<?> expectedDisjunction =
                    disjunction instanceof Disjunction ? (Disjunction<?>) disjunction
                            : new Disjunction<Formula<?>>(Of.of(disjunction));
            final Set<Litera<?>> tmp = new HashSet<Litera<?>>();
            for (final Formula<?> operand : expectedDisjunction.getOperands()) {
                if (operand instanceof AtomicFormula) {
                    tmp.add((AtomicFormula) operand);
                } else if (operand instanceof Negation<?>) {
                    final Negation<?> negation = (Negation<?>) operand;
                    if (negation.getNegated() instanceof AtomicFormula) {
                        tmp.add(new NegatedAtom((AtomicFormula) negation.getNegated()));
                    }
                }
            }
            setsExpected.add(tmp);
        }

        final Set<Set<Litera<?>>> setsActual =
                new HashSet<Set<Litera<?>>>(Functional.mapList(actual.getOperands(),
                        new Function<Disjunction<Litera<?>>, Set<Litera<?>>>() {

                            @Override
                            public Set<Litera<?>> apply(final Disjunction<Litera<?>> disjunction) {
                                return new HashSet<Litera<?>>(disjunction.getOperands());
                            }
                        }));
        return setsActual.equals(setsExpected);

    }

    /**
     * 
     */
    @Test
    public void testMakePNF() {
        final Formula<?> source =
                Parser.parseFormula("!exists x1((P(x1)&(any x2 P(x2)->exists y1 R(x1, y1)))->exists y2 R(x1, y2))");
        final Formula<?> matrixShouldBe =
                Parser.parseFormula("P(x1) & (!P(x2) V R(x1, y1)) & !R(x1, y2)");
        final List<Entry<Quantor, Variable>> prefixShouldBe =
                new ArrayList<Entry<Quantor, Variable>>(Of.of(

                new SimpleEntry<Quantor, Variable>(ForAny.QUANTOR, new Variable("x1")),

                new SimpleEntry<Quantor, Variable>(ExistsSuch.QUANTOR, new Variable("x2")),

                new SimpleEntry<Quantor, Variable>(ExistsSuch.QUANTOR, new Variable("y1")),

                new SimpleEntry<Quantor, Variable>(ForAny.QUANTOR, new Variable("y2"))));

        final PNF actual = org.kreved.mathlogic.algorithm.ResolutionsMethod.makePNF(source);
        assertEquals(prefixShouldBe, actual.getQuantorPrefix());
        assertTrue(equalCNF(matrixShouldBe, actual.getMatrix()));
    }

    /**
     * From {@link Formula#renameVariables(Function)}'s javadoc.
     */
    @Test
    public void testRenaming() {
        final Formula<?> source = Parser.parseFormula("any x (P(x) => exists x P(x))");
        final Formula<?> shouldBe = Parser.parseFormula("any y (P(y) => exists z P(z))");
        final Function<Variable, Variable> renamer = new Function<Variable, Variable>() {
            /**
             * 
             */
            private final Iterator<String> names = Of.of("y", "z").iterator();

            @Override
            public Variable apply(final Variable argument) {
                return new Variable(names.next());
            }
        };
        assertEquals(shouldBe, source.renameVariables(renamer));
    }

    /**
     * 
     */
    @Test
    public void testRenamingIndexed() {
        final Formula<?> source =
                Parser.parseFormula("!exists x ((P(x) & (any x P(x) -> exists y R(x, y))) -> exists y R(x, y))");
        final Formula<?> shouldBe =
                Parser.parseFormula("!exists x1((P(x1)&(any x2 P(x2)->exists y1 R(x1, y1)))->exists y2 R(x1, y2))");
        assertEquals(shouldBe, source.renameVariables(new BasicRenamer()));
    }
}
