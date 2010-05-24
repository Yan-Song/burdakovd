package com.appspot.milkydb.shared;

import com.googlecode.objectify.Key;

/**
 * 
 * @author burdakovd
 * 
 *         Классы, реализующие этот интерфейс должны помимо того, что иметь это
 *         поле, ещё и пометить его как @Parent
 */
public interface HasParent {
	Key<?> getParent();

	void setParent(Key<?> parent);
}
