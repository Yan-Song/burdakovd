package com.appspot.milkydb.shared.models;

import javax.persistence.Id;

import com.appspot.milkydb.shared.Model;
import com.appspot.milkydb.shared.dto.Dto;

@SuppressWarnings("serial")
public class Appointment implements Model, Dto {
	@Id
	private String name;

	public Appointment() {
	}

	public String getName() {
		return name;
	}

	public void setName(final String name) {
		this.name = name;
	}
}
