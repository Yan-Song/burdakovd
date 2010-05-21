package com.appspot.milkydb.shared.dto;

import com.appspot.milkydb.shared.HasKey;

@SuppressWarnings("serial")
public class LightEmployee implements Dto, HasKey<EncodedKey> {
	public EncodedKey key;
	public String name = "";
	public String post = "";
	public Double salary = 0.0;

	public LightEmployee() {
	}

	public LightEmployee(final EncodedKey key, final String name,
			final String post, final double salary) {
		this.key = key;
		this.name = name;
		this.post = post;
		this.salary = salary;
	}

	@Override
	public EncodedKey getKey() {
		return key;
	}

	@Override
	public void setKey(final EncodedKey key) {
		this.key = key;
	}
}
