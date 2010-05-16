package com.appspot.milkydb.server.models;

import javax.jdo.annotations.IdGeneratorStrategy;
import javax.jdo.annotations.IdentityType;
import javax.jdo.annotations.PersistenceCapable;
import javax.jdo.annotations.Persistent;
import javax.jdo.annotations.PrimaryKey;
import javax.persistence.Embedded;

import com.google.appengine.api.datastore.Key;

@PersistenceCapable(identityType = IdentityType.APPLICATION)
public class Employee {
	@PrimaryKey
	@Persistent(valueStrategy = IdGeneratorStrategy.IDENTITY)
	private Key key;

	@Persistent
	private String name;

	@Persistent
	@Embedded
	private ContactInfo contactInfo;

	@Persistent
	private String appointment;

	@Persistent
	private double salary;

	public String getAppointment() {
		return appointment;
	}

	public ContactInfo getContactInfo() {
		return contactInfo;
	}

	public Key getKey() {
		return key;
	}

	public String getName() {
		return name;
	}

	public double getSalary() {
		return salary;
	}

	public void setAppointment(final String appointment) {
		this.appointment = appointment;
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

	public void setSalary(final double salary) {
		this.salary = salary;
	}
}
