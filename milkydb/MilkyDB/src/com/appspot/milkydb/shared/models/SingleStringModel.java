package com.appspot.milkydb.shared.models;

import javax.persistence.Id;

import com.appspot.milkydb.shared.HasOwner;
import com.appspot.milkydb.shared.Model;
import com.appspot.milkydb.shared.dto.Dto;
import com.googlecode.objectify.Key;
import com.googlecode.objectify.annotation.Parent;

@SuppressWarnings("serial")
public class SingleStringModel implements Model, Dto, HasOwner {

	@Id
	private String name;

	@Parent
	private Key<?> owner;

	public SingleStringModel() {
		super();
	}

	public String getName() {
		return name;
	}

	public Key<?> getOwner() {
		return owner;
	}

	public void setName(final String name) {
		this.name = name;
	}

	public void setOwner(final Key<?> owner) {
		this.owner = owner;
	}

}