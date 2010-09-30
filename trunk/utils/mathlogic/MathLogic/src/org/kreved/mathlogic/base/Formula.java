package org.kreved.mathlogic.base;

import java.util.Set;

/**
 * @author burdakovd
 * 
 */
public interface Formula extends Substitutable<Formula> {

    /**
     * @param object
     *            другая формула
     * @return <code>true</code>, если эта формула совпадает с переданной
     */
    @Override
    boolean equals(Object object);

    /**
     * 
     * @return множество свободных переменных этой формулы
     */
    Set<Variable> getFreeVariables();

    /**
     * 
     * @return хэш, подчиняющийся стандартным законам, то есть
     *         <code>f1.equals(f2)</code> ->
     *         <code>f1.hashCode() == f2.hashCode()</code>
     */
    @Override
    int hashCode();

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