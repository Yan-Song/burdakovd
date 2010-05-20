package com.appspot.milkydb.shared.dto;

public interface HasKey<T> {
	public T getKey();

	public void setKey(T key);
}
