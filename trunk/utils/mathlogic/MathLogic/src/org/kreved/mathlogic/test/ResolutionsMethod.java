package org.kreved.mathlogic.test;

import static org.junit.Assert.assertEquals;

import java.util.Iterator;

import org.junit.Test;
import org.kreved.mathlogic.algorithm.BasicRenamer;
import org.kreved.mathlogic.base.Formula;
import org.kreved.mathlogic.base.Variable;
import org.kreved.mathlogic.util.Function;
import org.kreved.mathlogic.util.Of;
import org.kreved.mathlogic.util.Parser;

/**
 * @author burdakovd
 * 
 */
public final class ResolutionsMethod {

    /**
     * From {@link Formula#renameVariables(Function)} javadoc.
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
