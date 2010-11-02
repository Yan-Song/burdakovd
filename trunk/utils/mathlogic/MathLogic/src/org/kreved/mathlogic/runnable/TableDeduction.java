package org.kreved.mathlogic.runnable;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Collections;

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
    private static final String CONSTANTS = "abcd";

    /**
     * @param args
     *            параметры командной строки
     * @throws IOException
     *             в случае неполадок ввода/вывода
     */
    public static void main(final String[] args) throws IOException {

        final BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        final PrintWriter logger = new PrintWriter(System.out);

        logger.println("Введите формулу, имена констант могут начинаться с одного из символов: "
                + CONSTANTS);
        logger.flush();

        final Formula<?> formula =
                Parser.parseFormula(reader.readLine().trim(), new ConstantMatcher() {

                    @Override
                    public boolean isConstant(final String name) {
                        for (final char c : CONSTANTS.toCharArray()) {
                            if (name.startsWith(String.valueOf(c))) {
                                return true;
                            }
                        }
                        return false;
                    }
                });

        final SemanticTable t0 =
                new SemanticTable(Collections.<Formula<?>> emptySet(),
                        CommonUtils.singleElementSet(formula));

        final boolean result =
                org.kreved.mathlogic.algorithm.TableDeduction.doTableDeduction(t0,
                        new PrefixedConstantProvider("c", formula.getConstants()), logger);

        logger.println("Результат табличного вывода: " + result);
        logger.flush();
    }

    /**
     * Hide utility class ctor.
     */
    private TableDeduction() {

    }

}
