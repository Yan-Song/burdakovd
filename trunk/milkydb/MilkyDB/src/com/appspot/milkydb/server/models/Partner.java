package com.appspot.milkydb.server.models;

import javax.jdo.annotations.IdGeneratorStrategy;
import javax.jdo.annotations.IdentityType;
import javax.jdo.annotations.Inheritance;
import javax.jdo.annotations.InheritanceStrategy;
import javax.jdo.annotations.PersistenceCapable;
import javax.jdo.annotations.Persistent;
import javax.jdo.annotations.PrimaryKey;
import javax.persistence.Embedded;

import com.appspot.milkydb.shared.models.ContactInfo;
import com.google.appengine.api.datastore.Key;

@PersistenceCapable(identityType = IdentityType.APPLICATION)
@Inheritance(strategy = InheritanceStrategy.SUBCLASS_TABLE)
public class Partner {
	@PrimaryKey
	@Persistent(valueStrategy = IdGeneratorStrategy.IDENTITY)
	private Key key;

	@Persistent
	private String name;

	@Persistent
	@Embedded
	private ContactInfo contactInfo;

	public ContactInfo getContactInfo() {
		return contactInfo;
	}

	public Key getKey() {
		return key;
	}

	public String getName() {
		return name;
	}

	public void setContactInfo(final ContactInfo contactInfo) {
		this.contactInfo = contactInfo;
	}

	public void setKey(final Key key) {
		this.key = key;
	}

	public void setName(final String name) {
		this.name = name;
	}

}
