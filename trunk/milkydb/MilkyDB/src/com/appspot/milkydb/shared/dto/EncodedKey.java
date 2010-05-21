package com.appspot.milkydb.shared.dto;

@SuppressWarnings("serial")
public class EncodedKey implements Dto {
	private String value;

	@SuppressWarnings("unused")
	private EncodedKey() {

	}

	public EncodedKey(final String encoded) {
		this.value = encoded;
	}

	public String getValue() {
		return value;
	}

	public void setValue(final String key) {
		this.value = key;
	}
}
