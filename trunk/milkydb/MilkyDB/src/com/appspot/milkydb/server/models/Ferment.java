package com.appspot.milkydb.server.models;

import javax.jdo.annotations.IdGeneratorStrategy;
import javax.jdo.annotations.IdentityType;
import javax.jdo.annotations.PersistenceCapable;
import javax.jdo.annotations.Persistent;
import javax.jdo.annotations.PrimaryKey;

import com.google.appengine.api.datastore.Key;

@PersistenceCapable(identityType = IdentityType.APPLICATION)
public class Ferment {
	@PrimaryKey
	@Persistent(valueStrategy = IdGeneratorStrategy.IDENTITY)
	private Key key;

	@Persistent
	private String name;

	public Key getKey() {
		return key;
	}

	public String getName() {
		return name;
	}

	public void setKey(final Key key) {
		this.key = key;
	}

	public void setName(final String name) {
		this.name = name;
	}
}
