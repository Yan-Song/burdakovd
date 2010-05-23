package com.appspot.milkydb.shared.dto;

import com.googlecode.objectify.Key;

@SuppressWarnings("serial")
public class SingleKey implements Dto {

	public static SingleKey fromWebString(final String web) {
		return new SingleKey(Long.parseLong(web));
	}

	private Long value;

	@SuppressWarnings("unused")
	private SingleKey() {

	}

	public SingleKey(final Key<?> key) {
		setValue(key.getId());
	}

	public SingleKey(final Long value) {
		this.setValue(value);

	}

	public Long getValue() {
		return value;
	}

	public void setValue(final Long value) {
		this.value = value;
	}

	public String toWebString() {
		return value.toString();
	}
}
