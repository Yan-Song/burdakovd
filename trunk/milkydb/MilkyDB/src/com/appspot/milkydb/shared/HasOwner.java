package com.appspot.milkydb.shared;

import com.googlecode.objectify.Key;

public interface HasOwner {
	Key<?> getOwner();

	void setOwner(Key<?> owner);
}
