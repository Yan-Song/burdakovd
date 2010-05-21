package com.appspot.milkydb.shared;

public interface HasKey<T> {
	public T getKey();

	public void setKey(T key);
}
