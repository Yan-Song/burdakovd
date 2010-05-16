package com.appspot.milkydb.shared.dto;

import java.io.Serializable;

@SuppressWarnings("serial")
public class FullEmployee extends LightEmployee implements Serializable {

	public String address = "";
	public String phone = "";

	public FullEmployee() {
		super();
	}

	public FullEmployee(final String key, final String name, final String post,
			final double salary, final String address, final String phone) {
		super(key, name, post, salary);
		this.address = address;
		this.phone = phone;
	}
}
