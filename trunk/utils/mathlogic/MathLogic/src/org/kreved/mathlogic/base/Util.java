package org.kreved.mathlogic.base;

import java.util.Collections;
import java.util.HashSet;
import java.util.Set;

/**
 * @author burdakovd
 * 
 */
public final class Util {

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
     * Utility class.
     */
    private Util() {
    }

}
