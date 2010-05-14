package com.appspot.milkydb.server._models;

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
	private String name;

	@Persistent
	@Embedded
	private ContactInfo contactInfo;

	@Persistent
	private Appointment appointment;

	@Persistent
	private double salary;

	public Appointment getAppointment() {
		return appointment;
	}

	public ContactInfo getContactInfo() {
		return contactInfo;
	}

	public Long getId() {
		return id;
	}

	public String getName() {
		return name;
	}

	public void setAppointment(final Appointment appointment) {
		this.appointment = appointment;
	}

	public void setContactInfo(final ContactInfo contactInfo) {
		this.contactInfo = contactInfo;
	}

	public void setName(final String name) {
		this.name = name;
	}

	public void setSalary(double salary) {
		this.salary = salary;
	}

	public double getSalary() {
		return salary;
	}
}
