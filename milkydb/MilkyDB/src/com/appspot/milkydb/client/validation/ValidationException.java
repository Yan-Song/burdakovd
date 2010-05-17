package com.appspot.milkydb.client.validation;

import java.io.Serializable;
import java.util.HashMap;

@SuppressWarnings("serial")
public class ValidationException extends Exception implements Serializable {
	private HashMap<String, String> errors;

	/*
	 * for GWT-RPC
	 */
	@SuppressWarnings("unused")
	private ValidationException() {
	}

	public ValidationException(final HashMap<String, String> errors) {
		this.setErrors(errors);

	}

	public ValidationException(final String where, final String error) {
		setErrors(new HashMap<String, String>() {
			{
				put(where, error);
			}
		});
	}

	public HashMap<String, String> getErrors() {
		return errors;
	}

	private void setErrors(final HashMap<String, String> errors) {
		this.errors = errors;
	}
}
