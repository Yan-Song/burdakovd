package org.kreved.mathlogic.util;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * @author burdakovd
 * 
 */
public final class CommonUtils {

    /**
     * Склеивает указанные списки в указанном порядке.
     * 
     * @param <T>
     *            тип элементов списков
     * @param lists
     *            списки, которые нужно склеить
     * @return результат склейки переданных списков
     */
    public static <T> List<T> concatenate(final Iterable<? extends Collection<? extends T>> lists) {

        final List<T> ans = new ArrayList<T>();

        for (final Collection<? extends T> list : lists) {
            for (final T element : list) {
                ans.add(element);

            }
        }

        return Collections.unmodifiableList(ans);
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
    public static <T> boolean isSubSet(final Iterable<? extends T> first, final Set<T> second) {

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
    public static <T> List<T> concatenateWithMakingUnique(
            final Iterable<? extends Collection<? extends T>> lists) {

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
     *            тип элемента множества
     * @param element
     *            элементы множества
     * @return константное множество, состоящее из одного заданного элемента
     */
    @SuppressWarnings("unchecked")
    public static <T> Set<T> singleElementSet(final T element) {
        return unmodifiableSet(Arrays.asList(element));
    }

    /**
     * 
     * @param <T>
     *            тип элементов в множествах
     * @param first
     *            первая коллекция
     * @param second
     *            вторая коллекция
     * @return их объединение
     */
    public static <T> Set<T> union(final Collection<? extends T> first,
            final Collection<? extends T> second) {

        final Set<T> ans = new HashSet<T>();

        ans.addAll(first);
        ans.addAll(second);

        return Collections.unmodifiableSet(ans);
    }

    /**
     * 
     * @param <T>
     *            тип элементов в коллекциях
     * @param collections
     *            набор коллекций
     * @return объединение коллекций
     */
    public static <T> Set<T> union(final Iterable<? extends Collection<? extends T>> collections) {

        final Set<T> ans = new HashSet<T>();

        for (final Collection<? extends T> collection : collections) {
            ans.addAll(collection);
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
    public static <T> Set<T> unmodifiableSet(final Iterable<? extends T> elements) {

        final HashSet<T> set = new HashSet<T>();

        for (final T element : elements) {
            set.add(element);
        }

        return Collections.unmodifiableSet(set);
    }

    /**
     * Utility class.
     */
    private CommonUtils() {
    }
}
