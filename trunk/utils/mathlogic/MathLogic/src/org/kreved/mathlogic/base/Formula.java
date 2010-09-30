package org.kreved.mathlogic.base;

import java.util.Set;

/**
 * @author burdakovd
 * 
 */
public interface Formula {

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
}
