package com.appspot.milkydb.shared;

import java.io.Serializable;

@SuppressWarnings("serial")
public class LightEmployeeDetails implements Serializable {
	public String name;
	public String post;
	public double salary;

	public LightEmployeeDetails() {
	}

	public LightEmployeeDetails(final String name, final String post,
			final double salary) {
		this.name = name;
		this.post = post;
		this.salary = salary;
	}
}
