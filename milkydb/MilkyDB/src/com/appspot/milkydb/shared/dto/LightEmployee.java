package com.appspot.milkydb.shared.dto;

import java.io.Serializable;

@SuppressWarnings("serial")
public class LightEmployee implements Serializable {
	public String key;
	public String name = "";
	public String post = "";
	public Double salary = 0.0;

	public LightEmployee() {
	}

	public LightEmployee(final String key, final String name,
			final String post, final double salary) {
		this.key = key;
		this.name = name;
		this.post = post;
		this.salary = salary;
	}
}
