package org.kreved.mathlogic.util;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Random;
import java.util.Set;

import org.kreved.mathlogic.base.Constant;
import org.kreved.mathlogic.base.Formula;
import org.kreved.mathlogic.base.SemanticTable;

/**
 * @author burdakovd
 * 
 */
public final class MathUtil {

    /**
     * @param tree
     *            дерево формул
     * @param root
     *            корень нужного нам поддерева
     * @param tables
     *            таблицы
     * @param inLefts
     *            в левой ли части таблицы должна быть соответствующая формула
     * @param neededFormulas
     *            формула, одну из которых нужно найти
     * @return null, все ли ветки заданного дерева рано или поздно содержат
     *         заданную формулу в нужной стороне, или номер листа, путь к
     *         которому не содержит
     */
    @SuppressWarnings("unused")
    private static Integer allBranchesHas(final List<List<Integer>> tree, final int root,
            final List<SemanticTable> tables, final List<Boolean> inLefts,
            final List<Formula> neededFormulas) {

        for (int i = 0; i < neededFormulas.size(); ++i) {
            if ((inLefts.get(i) ? tables.get(root).getGamma() : tables.get(root).getDelta())
                    .contains(neededFormulas.get(i))) {
                return null;
            }
        }

        if (tree.get(root).isEmpty()) {
            return tables.get(root).isClosed() ? null : root;
        } else {
            for (final int child : tree.get(root)) {
                final Integer childResult =
                        allBranchesHas(tree, child, tables, inLefts, neededFormulas);
                if (childResult != null) {
                    return childResult;
                }
            }

            return null;
        }
    }

    /**
     * @param original
     *            исходная таблица
     * @param constantProvider
     *            множество неиспользованных констант
     * @param inLeft
     *            если <code>true</code>, то применяем правило к левой части
     *            таблицы, иначе к правой
     * @return множество таблиц, полученных применением к первой формуле
     *         левой/правой части таблицы соответствующего правила табличного
     *         вывода. <code>null</code>, если правило применить не к чему
     */
    @SuppressWarnings("unchecked")
    private static Set<SemanticTable> applyRule(final SemanticTable original,
            final Iterator<Constant> constantProvider, final boolean inLeft) {

        final Set<Formula> currentlyHasLeft = new HashSet<Formula>(original.getGamma());
        final Set<Formula> currentlyHasRight = new HashSet<Formula>(original.getDelta());

        final List<Formula> candidates = inLeft ? original.getGamma() : original.getDelta();

        // последовательно пытаемся применить правила к какой-либо из формул
        for (int i = 0; i < candidates.size(); ++i) {

            final Formula candidate = candidates.get(i);

            if (!candidate.isAtomic()) {

                final Set<SemanticTable> result =
                        inLeft ? candidate.applyTableDeductionLeft(constantProvider,
                                original.getConstants()) : candidate.applyTableDeductionRight(
                                constantProvider, original.getConstants());

                if (result.size() == 1) {
                    final SemanticTable table = result.iterator().next();

                    // если текущая формула сохранилась в новой таблице...
                    if ((inLeft ? table.getGamma() : table.getDelta()).contains(candidate)) {

                        // а также ничего нового не добавилось...
                        if (isSubSet(table.getGamma(), currentlyHasLeft)
                                && isSubSet(table.getDelta(), currentlyHasRight)) {
                            // получим таблицу, совпадающую с текущей
                            // этот кандидат нам не подходит
                            continue;
                        }
                    }
                }

                // этот кандидат подходит

                // формулы, к которым не удалось применить правило
                final List<Formula> junk = candidates.subList(0, i);

                // не рассмотренные формулы
                final List<Formula> remaining = candidates.subList(i + 1, candidates.size());

                final Set<SemanticTable> ans = new HashSet<SemanticTable>();

                for (final SemanticTable table : result) {
                    if (inLeft) {
                        final List<Formula> newLeft =
                                mergeWithMakingUnique(remaining, junk, table.getGamma());

                        final List<Formula> newRight =
                                mergeWithMakingUnique(original.getDelta(), table.getDelta());

                        ans.add(new SemanticTable(newLeft, newRight));
                    } else {
                        final List<Formula> newLeft =
                                mergeWithMakingUnique(original.getGamma(), table.getGamma());

                        final List<Formula> newRight =
                                mergeWithMakingUnique(remaining, junk, table.getDelta());

                        ans.add(new SemanticTable(newLeft, newRight));
                    }
                }

                System.out.println("Применяем правило вывода к [left=" + inLeft + "] " + candidate
                        + ", получаем " + result);

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
     * @return множество полученных таблиц
     */
    private static Set<SemanticTable> doSingleDeduction(final SemanticTable original,
            final Iterator<Constant> constantProvider, final boolean preferLeft) {

        final Set<SemanticTable> preferredCandidate =
                applyRule(original, constantProvider, preferLeft);

        if (preferredCandidate == null) {
            final Set<SemanticTable> unPreferredCandidate =
                    applyRule(original, constantProvider, !preferLeft);

            if (unPreferredCandidate == null) {
                // нет правил для применения, возвращаем исходную таблицу
                System.out.println("Нет правил для применения");
                return MathUtil.unmodifiableSet(original);
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
     * @return <code>true</code>, если был успешно применён табличный вывод
     */
    public static boolean doTableDeduction(final SemanticTable original,
            final Iterator<Constant> constantProvider) {

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
        System.out.println(String.format("T0 = %s", original));

        final List<SemanticTable> tables = new ArrayList<SemanticTable>();
        tables.add(original);

        final List<List<Integer>> tree = new ArrayList<List<Integer>>();
        tree.add(new ArrayList<Integer>());

        while (!pending.isEmpty()) {

            final SemanticTable current = pending.poll();
            final boolean currentSide = side.poll();
            ++popped;

            if (current.isClosed()) {
                System.out.println(String.format("T%d закрыта, обрабатывать её не нужно.", popped));
                continue;
            } else {
                if (current.isAtomic()) {
                    System.out.println(String.format(
                            "T%d не закрыта и атомарна, значит исходная таблица невыводима.",
                            pushed));
                    return false;
                }
                System.out.println(String.format("Рассмотрим таблицу T%d", popped));
            }

            final Set<SemanticTable> deduced =
                    doSingleDeduction(current, constantProvider, currentSide);

            if (deduced.contains(current)) {
                System.out.println(String.format(
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
                System.out.println(String.format("T%d = %s", pushed, table));

                if (table.isAtomic() && !table.isClosed()) {
                    System.out.println(String.format(
                            "T%d не закрыта и атомарна, значит исходная таблица невыводима.",
                            pushed));

                    return false;
                }
            }
        }

        System.out
                .println("Во всех ветвях получены закрытые таблицы, выполнен успешный табличный вывод.");

        return true;
    }

    /**
     * @param <T>
     *            тип элементов в множестве
     * @param oldSet
     *            исходное множество
     * @param exclude
     *            элемент, который нужно исключить
     * @return множество, полученное из исходного удалением заданного элемента
     */
    public static <T> Set<T> excluding(final Set<T> oldSet, final T exclude) {

        final Set<T> ans = new HashSet<T>(oldSet);

        ans.remove(exclude);

        return Collections.unmodifiableSet(ans);
    }

    /**
     * @param <T>
     *            тип элементов множества
     * @param first
     *            первая коллекция
     * @param second
     *            второе множество
     * @return принадлежат ли все элементы коллекции множеству
     */
    private static <T> boolean isSubSet(final Collection<? extends T> first, final Set<T> second) {

        for (final T element : first) {
            if (!second.contains(element)) {
                return false;
            }
        }

        return true;
    }

    /**
     * @param separator
     *            разделитель
     * @param objects
     *            перечисление объектов
     * @return склейка заданных объектов в строку с использованием указаннного
     *         сепаратора
     */
    public static String join(final String separator, final Iterable<?> objects) {

        final StringBuilder builder = new StringBuilder();

        boolean first = true;

        for (final Object object : objects) {
            if (first) {
                first = false;
            } else {
                builder.append(separator);
            }
            builder.append(object);
        }

        return builder.toString();
    }

    /**
     * Склеивает указанные списки в указанном порядке, но следит, чтобы не было
     * повторяющихся элементов.
     * <ul>
     * <li>Сохраняет порядок</li>
     * <li>Исключает повторы, сохраняет только первые вхождения для каждого
     * повтора</li>
     * </ul>
     * 
     * @param <T>
     *            тип элементов списков
     * @param lists
     *            списки, которые нужно склеить
     * @return результат склейки переданных списков
     */
    public static <T> List<T> mergeWithMakingUnique(final Collection<? extends T>... lists) {

        final Set<T> was = new HashSet<T>();
        final List<T> ans = new ArrayList<T>();

        for (final Collection<? extends T> list : lists) {
            for (final T element : list) {
                if (!was.contains(element)) {
                    was.add(element);
                    ans.add(element);
                }
            }
        }

        return Collections.unmodifiableList(ans);
    }

    /**
     * 
     * @param <T>
     *            тип элементов в множествах
     * @param sets
     *            набор множеств
     * @return их объединение
     */
    public static <T> Set<T> union(final Collection<? extends T>... sets) {

        final Set<T> ans = new HashSet<T>();

        for (final Collection<? extends T> set : sets) {
            ans.addAll(set);
        }

        return Collections.unmodifiableSet(ans);
    }

    /**
     * 
     * @param <T>
     *            тип элементов множества
     * @param elements
     *            элементы множества
     * @return константное множество, состоящее из заданных элементов
     */
    public static <T> Set<T> unmodifiableSet(final T... elements) {

        final HashSet<T> set = new HashSet<T>();

        for (final T element : elements) {
            set.add(element);
        }

        return Collections.unmodifiableSet(set);
    }

    /**
     * @param tree
     *            структура дерева
     * @param root
     *            корень
     * @param level
     *            текущий уровень
     * @param counts
     *            мап с количествами
     */
    @SuppressWarnings("unused")
    private static void updateCounts(final List<List<Integer>> tree, final int root,
            final int level, final Map<Integer, Integer> counts) {

        counts.put(level, counts.containsKey(level) ? counts.get(level) + 1 : 1);

        for (final int child : tree.get(root)) {
            updateCounts(tree, child, level + 1, counts);
        }

    }

    /**
     * Utility class.
     */
    private MathUtil() {
    }
}