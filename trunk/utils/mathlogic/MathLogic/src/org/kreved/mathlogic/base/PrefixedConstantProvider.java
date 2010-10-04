package org.kreved.mathlogic.base;

import java.util.Collection;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

/**
 * @author burdakovd
 * 
 */
public final class PrefixedConstantProvider implements Iterator<Constant> {

    /**
     * 
     */
    private long nextIndex = 0;

    /**
     * 
     */
    private final String prefix;

    /**
     * 
     */
    private final Set<Constant> forbidden;

    /**
     * @param forbidden
     *            список уже использованных констант
     * @param prefix
     *            префикс имен всех констант
     */
    public PrefixedConstantProvider(final String prefix,
            final Collection<? extends Constant> forbidden) {

        this.prefix = prefix;
        this.forbidden = new HashSet<Constant>(forbidden);
    }

    /*
     * (non-Javadoc)
     * 
     * @see java.util.Iterator#hasNext()
     */
    @Override
    public boolean hasNext() {
        return true;
    }

    /*
     * (non-Javadoc)
     * 
     * @see java.util.Iterator#next()
     */
    @Override
    public Constant next() {

        Constant ans;

        do {
            ++nextIndex;
            ans = new Constant(prefix + nextIndex);
        } while (forbidden.contains(ans));

        return ans;
    }

    /*
     * (non-Javadoc)
     * 
     * @see java.util.Iterator#remove()
     */
    @Override
    public void remove() {
        throw new UnsupportedOperationException();
    }

}
