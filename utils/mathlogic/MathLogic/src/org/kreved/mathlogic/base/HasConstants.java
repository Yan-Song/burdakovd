package org.kreved.mathlogic.base;

import java.util.Set;

/**
 * @author burdakovd
 * 
 */
public interface HasConstants {

    /**
     * 
     * @return множество использованных констант
     */
    Set<Constant> getConstants();
}
