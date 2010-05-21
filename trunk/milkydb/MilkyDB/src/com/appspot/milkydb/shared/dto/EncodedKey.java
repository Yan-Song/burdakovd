package com.appspot.milkydb.shared.dto;

@SuppressWarnings("serial")
public class EncodedKey implements Dto {
	private String key;

	@SuppressWarnings("unused")
	private EncodedKey() {

	}

	public EncodedKey(final String key) {
		this.key = key;
	}

	public String getKey() {
		return key;
	}

	public void setKey(final String key) {
		this.key = key;
	}
}
