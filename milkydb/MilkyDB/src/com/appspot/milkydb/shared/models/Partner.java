package com.appspot.milkydb.shared.models;

import java.util.HashMap;

import javax.persistence.Embedded;
import javax.persistence.Id;

import com.appspot.milkydb.client.validation.ValidationError;
import com.appspot.milkydb.client.validation.Validator;
import com.appspot.milkydb.shared.HasKey;
import com.appspot.milkydb.shared.HasParent;
import com.appspot.milkydb.shared.Validatable;
import com.appspot.milkydb.shared.dto.Dto;
import com.googlecode.objectify.Key;
import com.googlecode.objectify.annotation.Parent;

@SuppressWarnings("serial")
public class Partner implements Dto, HasKey<Long>, HasParent, Validatable {

	public static enum Fields implements Validatable.Fields {
		name, address, phoneNumber
	}

	@Parent
	private Key<?> parent;

	@Id
	private Long key;

	private String name = "";

	@Embedded
	private ContactInfo contactInfo = new ContactInfo();

	/**
	 * 
	 */
	public Partner() {
	}

	/**
	 * @param name
	 * @param contactInfo
	 */
	public Partner(final String name, final ContactInfo contactInfo) {
		this.name = name;
		this.contactInfo = contactInfo;
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

	public Key<?> getParent() {
		return parent;
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

	public void setParent(final Key<?> parent) {
		this.parent = parent;
	}

	@Override
	public void validate() throws ValidationError {
		final HashMap<Enum<? extends Validatable.Fields>, String> errors = new HashMap<Enum<? extends Validatable.Fields>, String>();

		if (!Validator.validateString(this.name, 1, 50)) {
			errors.put(Fields.name,
					"Имя должно быть непустой строкой не длиннее 50 символов");
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
