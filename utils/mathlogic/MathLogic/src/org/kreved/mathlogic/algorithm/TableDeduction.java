package org.kreved.mathlogic.algorithm;

import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Random;
import java.util.Set;

import org.kreved.mathlogic.base.Constant;
import org.kreved.mathlogic.base.Formula;
import org.kreved.mathlogic.base.SemanticTable;
import org.kreved.mathlogic.util.CommonUtils;
import org.kreved.mathlogic.util.Functional;
import org.kreved.mathlogic.util.Of;

/**
 * @author burdakovd
 * 
 */
public final class TableDeduction {

    /**
     * @param original
     *            исходная таблица
     * @param constantProvider
     *            множество неиспользованных констант
     * @param inLeft
     *            если <code>true</code>, то применяем правило к левой части
     *            таблицы, иначе к правой
     * @param logger
     *            вывод
     * @return множество таблиц, полученных применением к первой формуле
     *         левой/правой части таблицы соответствующего правила табличного
     *         вывода. <code>null</code>, если правило применить не к чему
     */
    private static Set<SemanticTable> applyRule(final SemanticTable original,
            final Iterator<Constant> constantProvider, final boolean inLeft,
            final PrintWriter logger) {

        final Set<Formula<?>> currentlyHasLeft = new HashSet<Formula<?>>(original.getGamma());
        final Set<Formula<?>> currentlyHasRight = new HashSet<Formula<?>>(original.getDelta());

        final List<Formula<?>> candidates = inLeft ? original.getGamma() : original.getDelta();

        // последовательно пытаемся применить правила к какой-либо из формул
        for (int i = 0; i < candidates.size(); ++i) {

            final Formula<?> candidate = candidates.get(i);

            if (!candidate.isAtomic()) {

                final Iterator<Constant> termProvider =
                        Functional.concat(Of.of(original.getConstants().iterator(),
                                Functional.take(1, constantProvider)).iterator());

                final Set<SemanticTable> result =
                        inLeft ? candidate.applyTableDeductionLeft(constantProvider, termProvider)
                                : candidate
                                        .applyTableDeductionRight(constantProvider, termProvider);

                if (result.size() == 1) {
                    final SemanticTable table = result.iterator().next();

                    // если текущая формула сохранилась в новой таблице...
                    if ((inLeft ? table.getGamma() : table.getDelta()).contains(candidate)) {

                        // а также ничего нового не добавилось...
                        if (CommonUtils.isSubSet(table.getGamma(), currentlyHasLeft)
                                && CommonUtils.isSubSet(table.getDelta(), currentlyHasRight)) {
                            // получим таблицу, совпадающую с текущей
                            // этот кандидат нам не подходит
                            continue;
                        }
                    }
                }

                // этот кандидат подходит

                // формулы, к которым не удалось применить правило
                final List<Formula<?>> junk = candidates.subList(0, i);

                // не рассмотренные формулы
                final List<Formula<?>> remaining = candidates.subList(i + 1, candidates.size());

                final Set<SemanticTable> ans = new HashSet<SemanticTable>();

                for (final SemanticTable table : result) {
                    if (inLeft) {
                        final List<Formula<?>> newLeft =
                                CommonUtils.concatenateWithMakingUnique(Of.of(remaining, junk,
                                        table.getGamma()));

                        final List<Formula<?>> newRight =
                                CommonUtils.concatenateWithMakingUnique(Of.of(original.getDelta(),
                                        table.getDelta()));

                        ans.add(new SemanticTable(newLeft, newRight));
                    } else {
                        final List<Formula<?>> newLeft =
                                CommonUtils.concatenateWithMakingUnique(Of.of(original.getGamma(),
                                        table.getGamma()));

                        final List<Formula<?>> newRight =
                                CommonUtils.concatenateWithMakingUnique(Of.of(remaining, junk,
                                        table.getDelta()));

                        ans.add(new SemanticTable(newLeft, newRight));
                    }
                }

                logger.println("Применяем правило вывода " + (inLeft ? "L" : "R") + " "
                        + candidate.symbol());

                return Collections.unmodifiableSet(ans);
            }
        }

        return null;
    }

    /**
     * @param original
     *            исходная таблица
     * @param constantProvider
     *            множество неиспользованных констант
     * @param preferLeft
     *            <code>true</code>, если нужно педпочитать использовать левые
     *            правила, <code>false</code> - если правые
     * @param logger
     *            вывод
     * @return множество полученных таблиц
     */
    private static Set<SemanticTable> doSingleDeduction(final SemanticTable original,
            final Iterator<Constant> constantProvider, final boolean preferLeft,
            final PrintWriter logger) {

        final Set<SemanticTable> preferredCandidate =
                applyRule(original, constantProvider, preferLeft, logger);

        if (preferredCandidate == null) {
            final Set<SemanticTable> unPreferredCandidate =
                    applyRule(original, constantProvider, !preferLeft, logger);

            if (unPreferredCandidate == null) {
                // нет правил для применения, возвращаем исходную таблицу
                logger.println("Нет правил для применения");
                return CommonUtils.unmodifiableSet(Of.of(original));
            } else {
                return unPreferredCandidate;
            }
        } else {
            return preferredCandidate;
        }

    }

    /**
     * @param original
     *            семантическая таблица
     * @param constantProvider
     *            множество неиспользованных констант
     * @param logger
     *            вывод
     * @return <code>true</code>, если был успешно применён табличный вывод
     */
    public static boolean doTableDeduction(final SemanticTable original,
            final Iterator<Constant> constantProvider, final PrintWriter logger) {

        final Random random = new Random(137);

        int pushed = -1;
        int popped = -1;

        final Queue<SemanticTable> pending = new LinkedList<SemanticTable>();
        // параллельно с таблицами храним также сторону, к которой нужно
        // применить правила
        final Queue<Boolean> side = new LinkedList<Boolean>();

        pending.add(original);
        side.add(true);
        ++pushed;
        logger.println(String.format("T0 = %s", original));

        final List<SemanticTable> tables = new ArrayList<SemanticTable>();
        tables.add(original);

        final List<List<Integer>> tree = new ArrayList<List<Integer>>();
        tree.add(new ArrayList<Integer>());

        while (!pending.isEmpty()) {

            final SemanticTable current = pending.poll();
            final boolean currentSide = side.poll();
            ++popped;

            if (current.isClosed()) {
                logger.println(String.format("T%d закрыта, обрабатывать её не нужно.", popped));
                continue;
            } else {
                if (current.isAtomic()) {
                    logger.println(String.format(
                            "T%d не закрыта и атомарна, значит исходная таблица невыводима.",
                            pushed));
                    return false;
                }
                logger.println(String.format("Рассмотрим таблицу T%d", popped));
            }

            final Set<SemanticTable> deduced =
                    doSingleDeduction(current, constantProvider, currentSide, logger);

            if (deduced.contains(current)) {
                logger.println(String.format(
                        "Таблица T%d = %s вызывает зацикливание, табличный вывод неосуществим.",
                        popped, current));
                return false;
            }

            for (final SemanticTable table : deduced) {

                pending.add(table);
                tables.add(table);
                tree.add(new ArrayList<Integer>());
                side.add(random.nextBoolean());
                ++pushed;
                tree.get(popped).add(pushed);
                logger.println(String.format("T%d = %s", pushed, table));

                if (table.isAtomic() && !table.isClosed()) {
                    logger.println(String.format(
                            "T%d не закрыта и атомарна, значит исходная таблица невыводима.",
                            pushed));

                    return false;
                }
            }
        }

        logger.println("Во всех ветвях получены закрытые таблицы, выполнен успешный табличный вывод.");

        return true;
    }

    /**
     * Hide utility class ctor.
     */
    private TableDeduction() {

    }

}
