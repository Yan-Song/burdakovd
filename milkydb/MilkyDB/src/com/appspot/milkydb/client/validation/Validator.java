package com.appspot.milkydb.client.validation;

import com.appspot.milkydb.shared.dto.TimeSpan;
import com.google.appengine.api.datastore.Text;

public class Validator {
	public static boolean validateDouble(final Double d, final Double minValue,
			final Double maxValue) {
		return d != null && d >= minValue && d <= maxValue;
	}

	public static boolean validateFloat(final Float d, final Float minValue,
			final Float maxValue) {
		return d != null && d >= minValue && d <= maxValue;
	}

	public static boolean validateString(final String s, final int minLength,
			final int maxLength) {
		return s != null && s.length() >= minLength && s.length() <= maxLength;
	}

	public static boolean validateString(final Text text, final int minLength,
			final int maxLength) {
		return validateString(text.getValue(), minLength, maxLength);
	}

	public static boolean validateTimeSpan(final TimeSpan span,
			final long minSeconds, final long maxSeconds) {
		if (span == null) {
			return false;
		}

		final long seconds = span.getSeconds();

		return seconds >= minSeconds && seconds <= maxSeconds;
	}

	public static boolean validateWord(final String word) {
		return validateString(word, 1, 50) && !word.contains(" ");
	}
}
