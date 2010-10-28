package org.kreved.mathlogic.util;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

/**
 * Берёт на себя бремя ворнингов, связанных с преобразованием varargs в
 * {@link List}.
 * 
 * @author burdakovd
 * 
 */
public final class Of {
    /**
     * 
     * @param <T>
     *            тип элемента
     * @param element
     *            элемент
     * @return {@link List} из одного элемента
     */
    @SuppressWarnings("unchecked")
    public static <T> List<T> of(final T element) {
        return varargsOf(element);
    }

    /**
     * 
     * @param <T>
     *            тип элементов
     * @param e1
     *            первый элемент
     * @param e2
     *            второй элемент
     * @return {@link List} из переданных элементов
     */
    @SuppressWarnings("unchecked")
    public static <T> List<T> of(final T e1, final T e2) {
        return varargsOf(e1, e2);
    }

    /**
     * 
     * @param <T>
     *            тип элементов
     * @param e1
     *            первый элемент
     * @param e2
     *            второй элемент
     * @param e3
     *            третий элемент
     * @return {@link List} из переданных элементов
     */
    @SuppressWarnings("unchecked")
    public static <T> List<T> of(final T e1, final T e2, final T e3) {
        return varargsOf(e1, e2, e3);
    }

    /**
     * 
     * @param <T>
     *            тип элементов
     * @param e1
     *            первый элемент
     * @param e2
     *            второй элемент
     * @param e3
     *            третий элемент
     * @param e4
     *            четвертый элемент
     * @return {@link List} из переданных элементов
     */
    @SuppressWarnings("unchecked")
    public static <T> List<T> of(final T e1, final T e2, final T e3, final T e4) {
        return varargsOf(e1, e2, e3);
    }

    /**
     * 
     * @param <T>
     *            тип элементов
     * @param elements
     *            элементы
     * @return {@link List} из переданных элементов
     */
    private static <T> List<T> varargsOf(final T... elements) {
        return Collections.unmodifiableList(Arrays.asList(elements));
    }

    /**
     * Hide utility class ctor.
     */
    private Of() {
    }

}
