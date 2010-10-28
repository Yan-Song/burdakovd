package org.kreved.mathlogic.algorithm;

import java.util.HashSet;
import java.util.Set;

import org.kreved.mathlogic.base.Variable;
import org.kreved.mathlogic.util.Function;

/**
 * Класс, пытающийся дописать к имени переменной индекс, увеличивая его при
 * совпадении с уже использованными.
 * 
 * @author burdakovd
 * 
 */
public final class BasicRenamer implements Function<Variable, Variable> {

    /**
     * Множество использованных имён.
     */
    private final Set<String> used = new HashSet<String>();

    /*
     * (non-Javadoc)
     * 
     * @see org.kreved.mathlogic.util.Function#apply(java.lang.Object)
     */
    @Override
    public Variable apply(final Variable argument) {

        String candidate;
        int index = 1;

        do {
            candidate = argument.getName() + index;
            ++index;
        } while (used.contains(candidate));

        used.add(candidate);

        return new Variable(candidate);
    }

}
