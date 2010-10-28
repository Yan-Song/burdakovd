package org.kreved.mathlogic.util;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;

/**
 * @author burdakovd
 * 
 */
public final class Functional {

    /**
     * 
     * @param <T>
     *            тип аргументов последовательности
     * @param predicate
     *            условие
     * @param elements
     *            последовательность
     * @return <code>true</code>, если условие выполняется на всех элементах
     *         последовательности
     */
    public static <T> boolean all(final Predicate<? super T> predicate,
            final Iterable<? extends T> elements) {

        for (final T element : elements) {
            if (!predicate.apply(element)) {
                return false;
            }
        }

        return true;
    }

    /**
     * Применение функции ко всем элементам последовательности.
     * 
     * @param <P>
     *            тип элементов исходной последовательности
     * @param <Q>
     *            тип элементов результирующей последовательности
     * @param source
     *            исходная последовательность
     * @param function
     *            функция, которую нужно применить ко всем элементам исходной
     *            последовательности
     * @return последовательность результатов применения заданной функции к
     *         элементам исходной последовательности
     */
    public static <P, Q> Iterable<Q> map(final Iterable<? extends P> source,
            final Function<? super P, ? extends Q> function) {

        return new Iterable<Q>() {

            @Override
            public Iterator<Q> iterator() {

                return new AbstractIterator<Q>() {

                    private final Iterator<? extends P> sourceIterator = source.iterator();

                    @Override
                    protected Q computeNext() {
                        if (sourceIterator.hasNext()) {
                            return function.apply(sourceIterator.next());
                        } else {
                            return endOfData();
                        }
                    }
                };
            }
        };
    }

    /**
     * Применение функции ко всем элементам списка.
     * 
     * @param <P>
     *            тип элементов исходного списка
     * @param <Q>
     *            тип элементов результирующего списка
     * @param source
     *            исходный список
     * @param function
     *            функция, которую нужно применить ко всем элементам исходного
     *            списка
     * @return список результатов применения заданной функции к элементам
     *         исходного списка
     */
    public static <P, Q> List<Q> mapList(final List<? extends P> source,
            final Function<? super P, ? extends Q> function) {

        final List<Q> ans = new ArrayList<Q>();

        for (final Q q : map(source, function)) {
            ans.add(q);
        }

        return Collections.unmodifiableList(ans);
    }

    /**
     * Hide utility class ctor.
     */
    private Functional() {
    }
}
