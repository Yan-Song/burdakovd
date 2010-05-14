package com.appspot.milkydb.server._models;

import java.util.Set;

import javax.jdo.annotations.IdGeneratorStrategy;
import javax.jdo.annotations.IdentityType;
import javax.jdo.annotations.PersistenceCapable;
import javax.jdo.annotations.Persistent;
import javax.jdo.annotations.PrimaryKey;

@PersistenceCapable(identityType = IdentityType.APPLICATION)
public class Appointment {
	@PrimaryKey
	@Persistent(valueStrategy = IdGeneratorStrategy.IDENTITY)
	private Long id;

	@Persistent
	private String name;

	@Persistent(mappedBy = "appointment")
	private Set<Employee> employees;

	public Set<Employee> getEmployees() {
		return employees;
	}

	public Long getId() {
		return id;
	}

	public String getName() {
		return name;
	}

	public void setEmployees(final Set<Employee> employees) {
		this.employees = employees;
	}

	public void setName(final String name) {
		this.name = name;
	}
}
