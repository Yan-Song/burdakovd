package com.appspot.milkydb.client.validation;

public class Validator {
	public static boolean validateDouble(final Double d, final Double minValue,
			final Double maxValue) {
		return d != null && d >= minValue && d <= maxValue;
	}

	public static boolean validateString(final String s, final int minLength,
			final int maxLength) {
		return s != null && s.length() >= minLength && s.length() <= maxLength;
	}
}
