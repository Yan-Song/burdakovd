package com.appspot.milkydb.shared.transferObjects;

import java.io.Serializable;

@SuppressWarnings("serial")
public class LightEmployee implements Serializable {
	public String name;
	public String post;
	public double salary;

	public LightEmployee() {
	}

	public LightEmployee(final String name, final String post,
			final double salary) {
		this.name = name;
		this.post = post;
		this.salary = salary;
	}
}
