package org.kreved.mathlogic.base;

import java.util.Collection;
import java.util.Iterator;
import java.util.Map.Entry;
import java.util.Set;

import org.kreved.mathlogic.util.Function;

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
            Iterator<? extends Term> terms);

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
            Iterator<? extends Term> terms);

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

    /**
     * Переименовать связанные кванторами переменные в формуле в соответствии с
     * заданным правилом.
     * <p>
     * renamer <b>не</b> обязан возвращать одинаковый результат для
     * повторяющихся вызовов с одним и тем же аргументом.
     * <p>
     * renamer будет вызван <b>один раз</b> для каждого квантора в формуле,
     * переменная в кванторе и все её связанные вхождения будут заменены на
     * результат этого вызова renamer.
     * <p>
     * Пример: если renamer возвращает <code>y</code> при первом вызове и
     * <code>z</code> при втором, то применение этого метода к формулe
     * <code>any x (P(x) => exists x P(x))</code> вернёт
     * <code>any y (P(y) => exists z P(z))</code>
     * <p>
     * Замены (и соответственно вызовы renamer) происходят слева направо (в
     * соответствии с нормальным порядком вычислений)
     * 
     * @param renamer
     *            функция переименования
     * @return результат переименования
     */
    T renameVariables(Function<Variable, Variable> renamer);

    /**
     * Представление для пользователя.
     * 
     * @return короткую строку, характеризующую класс этой формулы
     */
    String symbol();

    /**
     * Избавиться от импликации в формуле, протолкнуть отрицания к атомарным
     * формулам и вынести кванторы.
     * <p>
     * Предусловие: перед вызовом этой функции для каждой переменной
     * <ul>
     * <li>либо все вхождения связаны одним и тем же квантором</li>
     * <li>либо все вхождения свободны</li>
     * </ul>
     * 
     * @param needNegate
     *            нужно ли применить отрицание к формуле перед преобразованием
     * 
     * @return пару "кванторы, матрица"
     */
    Entry<Collection<Entry<Quantor, Variable>>, PrimitiveFormula<?>>
            toPrimitive(boolean needNegate);
}
