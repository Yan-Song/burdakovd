package com.appspot.milkydb.shared.models;

import java.util.HashMap;

import javax.persistence.Embedded;
import javax.persistence.Id;

import com.appspot.milkydb.client.validation.ValidationError;
import com.appspot.milkydb.client.validation.Validator;
import com.appspot.milkydb.shared.HasKey;
import com.appspot.milkydb.shared.HasOwner;
import com.appspot.milkydb.shared.Model;
import com.appspot.milkydb.shared.Validatable;
import com.appspot.milkydb.shared.dto.Dto;
import com.googlecode.objectify.Key;
import com.googlecode.objectify.annotation.Parent;

@SuppressWarnings("serial")
public class Employee implements HasKey<Long>, Validatable, Dto, Model,
		HasOwner {

	public enum Fields implements Validatable.Fields {
		name, post, salary, address, phoneNumber
	}

	@Id
	private Long key;

	@Parent
	private Key<?> owner;

	private String name;

	@Embedded
	private ContactInfo contactInfo;

	private String appointment;

	private double salary;

	public Employee() {
	}

	public Employee(final Long key, final String name,
			final ContactInfo contactInfo, final String appointment,
			final double salary) {
		super();
		this.key = key;
		this.name = name;
		this.contactInfo = contactInfo;
		this.appointment = appointment;
		this.salary = salary;
	}

	public String getAppointment() {
		return appointment;
	}

	public ContactInfo getContactInfo() {
		return contactInfo;
	}

	public Long getKey() {
		return key;
	}

	public String getName() {
		return name;
	}

	public Key<?> getOwner() {
		return owner;
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

	public void setKey(final Long key) {
		this.key = key;
	}

	public void setName(final String name) {
		this.name = name;
	}

	public void setOwner(final Key<?> owner) {
		this.owner = owner;
	}

	public void setSalary(final double salary) {
		this.salary = salary;
	}

	@Override
	public void validate() throws ValidationError {

		final HashMap<Enum<? extends Validatable.Fields>, String> errors = new HashMap<Enum<? extends Validatable.Fields>, String>();

		if (!Validator.validateString(this.name, 1, 50)) {
			errors.put(Fields.name,
					"Имя должно быть непустой строкой не длиннее 50 символов");
		}

		if (!Validator.validateString(this.appointment, 1, 50)) {
			errors
					.put(Fields.post,
							"Должность должна быть непустой строкой не длиннее 50 символов");
		}

		if (!Validator.validateDouble(this.salary, 0.0, 1000000.0)) {
			errors.put(Fields.salary, "Оклад должен быть положительным числом");
		}

		if (!Validator.validateString(this.contactInfo.getAddress(), 1, 500)) {
			errors
					.put(Fields.address,
							"Адрес должен быть непустой строкой не длиннее 500 символов");
		}

		if (!Validator.validateString(this.contactInfo.getAddress(), 1, 50)) {
			errors
					.put(Fields.phoneNumber,
							"Телефон должен быть непустой строкой не длиннее 50 символов");
		}

		if (!errors.isEmpty()) {
			throw new ValidationError(errors);
		}
	}
}
