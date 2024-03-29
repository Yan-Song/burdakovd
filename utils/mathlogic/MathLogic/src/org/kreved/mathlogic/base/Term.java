package org.kreved.mathlogic.base;

import java.util.Set;

/**
 * Терм.
 * 
 * @author burdakovd
 * 
 */
public interface Term extends Substitutable<Term>, HasConstants {

    /**
     * 
     * @return множество переменных, используемых этим термом
     */
    Set<Variable> getVariables();
}
