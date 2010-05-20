package com.appspot.milkydb.client.validation;

import java.io.Serializable;
import java.util.HashMap;

@SuppressWarnings("serial")
public class ValidationError extends Exception implements Serializable {
	private HashMap<String, String> errors;

	/*
	 * for GWT-RPC
	 */
	@SuppressWarnings("unused")
	private ValidationError() {
	}

	public ValidationError(final HashMap<String, String> errors) {
		this.setErrors(errors);

	}

	public ValidationError(final String where, final String error) {
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
