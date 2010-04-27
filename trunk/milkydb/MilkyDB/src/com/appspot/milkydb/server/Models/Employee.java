package com.appspot.milkydb.server.Models;

import javax.jdo.annotations.IdGeneratorStrategy;
import javax.jdo.annotations.IdentityType;
import javax.jdo.annotations.PersistenceCapable;
import javax.jdo.annotations.Persistent;
import javax.jdo.annotations.PrimaryKey;
import javax.persistence.Embedded;

@PersistenceCapable(identityType = IdentityType.APPLICATION)
public class Employee {
	@PrimaryKey
	@Persistent(valueStrategy = IdGeneratorStrategy.IDENTITY)
	private Long id;

	@Persistent
	@Embedded
	private ContactInfo contactInfo;

	public ContactInfo getContactInfo() {
		return contactInfo;
	}

	public Long getId() {
		return id;
	}

	public void setContactInfo(final ContactInfo contactInfo) {
		this.contactInfo = contactInfo;
	}
}
