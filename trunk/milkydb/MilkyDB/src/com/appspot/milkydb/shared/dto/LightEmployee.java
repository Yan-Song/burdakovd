package com.appspot.milkydb.shared.dto;

import com.appspot.milkydb.shared.HasKey;

@SuppressWarnings("serial")
public class LightEmployee implements Dto, HasKey<Long> {
	public Long key;
	public String name = "";
	public String post = "";
	public Double salary = 0.0;

	public LightEmployee() {
	}

	public LightEmployee(final Long key, final String name, final String post,
			final double salary) {
		this.key = key;
		this.name = name;
		this.post = post;
		this.salary = salary;
	}

	@Override
	public Long getKey() {
		return key;
	}

	@Override
	public void setKey(final Long key) {
		this.key = key;
	}
}
