package com.appspot.milkydb.client.validation;

public interface CanDisplayValidationExceptions {
	void clearErrors();

	void showValidationError(ValidationException exception);
}
