package com.appspot.milkydb.client.validation;

import java.util.HashMap;

import com.appspot.milkydb.shared.Validatable;
import com.appspot.milkydb.shared.dto.Dto;

@SuppressWarnings("serial")
public class ValidationError extends Exception implements Dto {

	private HashMap<Enum<? extends Validatable.Fields>, String> errors = new HashMap<Enum<? extends Validatable.Fields>, String>();

	/*
	 * for GWT-RPC
	 */
	@SuppressWarnings("unused")
	private ValidationError() {
	}

	public ValidationError(final Enum<? extends Validatable.Fields> where,
			final String error) {
		errors.put(where, error);
	}

	public ValidationError(
			final HashMap<Enum<? extends Validatable.Fields>, String> errors) {
		this.setErrors(errors);

	}

	public HashMap<Enum<? extends Validatable.Fields>, String> getErrors() {
		return errors;
	}

	private void setErrors(
			final HashMap<Enum<? extends Validatable.Fields>, String> errors) {
		this.errors = errors;
	}
}
