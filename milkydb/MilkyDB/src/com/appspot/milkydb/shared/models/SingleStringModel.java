package com.appspot.milkydb.shared.models;

import javax.persistence.Id;

import com.appspot.milkydb.shared.HasParent;
import com.appspot.milkydb.shared.Model;
import com.appspot.milkydb.shared.dto.Dto;
import com.googlecode.objectify.Key;
import com.googlecode.objectify.annotation.Parent;

@SuppressWarnings("serial")
public class SingleStringModel implements Model, Dto, HasParent {

	@Id
	private String name;

	@Parent
	private Key<?> parent;

	public SingleStringModel() {
		super();
	}

	public String getName() {
		return name;
	}

	public Key<?> getParent() {
		return parent;
	}

	public void setName(final String name) {
		this.name = name;
	}

	public void setParent(final Key<?> parent) {
		this.parent = parent;
	}

}