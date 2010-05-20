package com.appspot.milkydb.client.validation;

public interface CanDisplayValidationErrors {
	void clearErrors();

	void showValidationError(ValidationError exception);
}
