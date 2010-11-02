package org.kreved.mathlogic.test;

import java.io.IOException;
import java.io.OutputStream;

/**
 * @author burdakovd
 * 
 */
public final class NullOutputStream extends OutputStream {

    /*
     * (non-Javadoc)
     * 
     * @see java.io.OutputStream#write(int)
     */
    @Override
    public void write(final int b) throws IOException {
        // do nothing
    }

}
