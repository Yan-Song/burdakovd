package com.appspot.milkydb.shared.dto;

import java.util.HashMap;

import com.appspot.milkydb.client.validation.ValidationError;
import com.appspot.milkydb.client.validation.Validator;
import com.appspot.milkydb.shared.Validatable;

@SuppressWarnings("serial")
public class FullEmployee extends LightEmployee implements Validatable {

	public enum Fields implements Validatable.Fields {
		name, post, salary, address, phoneNumber
	}

	public String address = "";
	public String phone = "";

	public FullEmployee() {
		super();
	}

	public FullEmployee(final EncodedKey key, final String name,
			final String post, final double salary, final String address,
			final String phone) {
		super(key, name, post, salary);
		this.address = address;
		this.phone = phone;
	}

	@Override
	public void validate() throws ValidationError {
		final HashMap<Enum<? extends Validatable.Fields>, String> errors = new HashMap<Enum<? extends Validatable.Fields>, String>();

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
			throw new ValidationError(errors);
		}
	}
}
