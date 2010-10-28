package org.kreved.mathlogic.base;

import java.util.Iterator;
import java.util.Set;

/**
 * @param <T>
 *            тип результата применения подстановки к этой формуле
 * @author burdakovd
 * 
 */
public interface Formula<T extends Formula<?>> extends Substitutable<T>, HasConstants {

    /**
     * @param constantProvider
     *            итератор по множеству ранее не использованных констант
     * @param terms
     *            последовательность термов для подстановки
     * @return набор таблиц, в которые преобразуется данная формула при
     *         применении соответствующего правила табличного вывода, если она
     *         стоит слева
     */
    Set<SemanticTable> applyTableDeductionLeft(Iterator<Constant> constantProvider,
            Iterable<? extends Term> terms);

    /**
     * @param constantProvider
     *            итератор по множеству ранее не использованных констант
     * @param terms
     *            последовательность термов для подстановки
     * @return набор таблиц, в которые преобразуется данная формула при
     *         применении соответствующего правила табличного вывода, если она
     *         стоит справа
     */
    Set<SemanticTable> applyTableDeductionRight(Iterator<Constant> constantProvider,
            Iterable<? extends Term> terms);

    /**
     * @param object
     *            другая формула
     * @return <code>true</code>, если эта формула совпадает с переданной
     */
    @Override
    boolean equals(Object object);

    /**
     * @return множество констант, использованных в формуле
     */
    @Override
    Set<Constant> getConstants();

    /**
     * 
     * @return множество свободных переменных этой формулы
     */
    Set<Variable> getFreeVariables();

    /**
     * 
     * @return приоритет внешней операции этой формулы
     */
    int getPriority();

    /**
     * 
     * @return хэш, подчиняющийся стандартным законам, то есть
     *         <code>f1.equals(f2)</code> ->
     *         <code>f1.hashCode() == f2.hashCode()</code>
     */
    @Override
    int hashCode();

    /**
     * @return атомарна ли формула
     */
    boolean isAtomic();

    /**
     * Проверяет верно ли, что переменная <code>variable</code> свободна для
     * терма <code>term</code> в формуле <code>this</code>.
     * <p>
     * По определению это значит, что любое свободное вхождение переменной
     * <code>variable</code> в формуле <code>this</code> не лежит в области
     * действия ни одного квантора, связывающего переменную из множества
     * <code>Var_{term}</code>
     * 
     * @param variable
     *            переменная, которую нужно заменить на терм
     * @param term
     *            терм
     * @return верно ли, что переменная <code>variable</code> свободна для терма
     *         <code>term</code> в формуле <code>this</code>
     */
    boolean isVariableFreeForTerm(Variable variable, Term term);
}
