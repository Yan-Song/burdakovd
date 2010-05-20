package com.appspot.milkydb.shared.dto;

import java.io.Serializable;
import java.util.HashMap;

import com.appspot.milkydb.client.validation.ValidationException;
import com.appspot.milkydb.client.validation.Validator;

@SuppressWarnings("serial")
public class FullEmployee extends LightEmployee implements Serializable,
		Validatable, HasKey<String> {

	public interface Fields extends Validatable.Fields {
		final static String name = "name";
		final static String post = "post";
		final static String salary = "salary";
		final static String address = "address";
		final static String phoneNumber = "phoneNumber";
	}

	public String address = "";
	public String phone = "";

	public FullEmployee() {
		super();
	}

	public FullEmployee(final String key, final String name, final String post,
			final double salary, final String address, final String phone) {
		super(key, name, post, salary);
		this.address = address;
		this.phone = phone;
	}

	@Override
	public String getKey() {
		return this.key;
	}

	@Override
	public void setKey(final String key) {
		this.key = key;
	}

	@Override
	public void validate() throws ValidationException {
		final HashMap<String, String> errors = new HashMap<String, String>();

		if (!Validator.validateString(this.name, 1, 50)) {
			errors.put(Fields.name,
					"Имя должно быть непустой строкой не длиннее 50 символов");
		}

		if (!Validator.validateString(this.post, 1, 50)) {
			errors
					.put(Fields.post,
							"Должность должна быть непустой строкой не длиннее 50 символов");
		}

		if (!Validator.validateDouble(this.salary, 0.0, 1000000.0)) {
			errors.put(Fields.salary, "Оклад должен быть положительным числом");
		}

		if (!Validator.validateString(this.address, 1, 500)) {
			errors
					.put(Fields.address,
							"Адрес должен быть непустой строкой не длиннее 500 символов");
		}

		if (!Validator.validateString(this.phone, 1, 50)) {
			errors
					.put(Fields.phoneNumber,
							"Телефон должен быть непустой строкой не длиннее 50 символов");
		}

		if (!errors.isEmpty()) {
			throw new ValidationException(errors);
		}
	}
}
