package com.appspot.milkydb.shared.dto;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import com.appspot.milkydb.client.validation.ValidationError;
import com.appspot.milkydb.client.validation.Validator;
import com.appspot.milkydb.shared.Validatable;

@SuppressWarnings("serial")
public class FullProductClass extends LightProductClass implements Validatable,
		Serializable {

	public enum Fields implements Validatable.Fields {
		name, fatness, calorificValue, storageLife, packing, storageConstraints, transportationConstraints, ferments, microElements
	}

	private String packing;

	private String storageConstraints;

	private String transportationConstraints;

	private ArrayList<String> ferments;

	private ArrayList<String> microElements;

	protected FullProductClass() {
		super();
	}

	public FullProductClass(final EncodedKey key, final String name,
			final Float fatness, final Float calorificValue,
			final TimeSpan storageLife, final String packing,
			final String storageConstraints,
			final String transportationConstraints,
			final List<String> ferments, final List<String> microElements) {
		super(key, name, fatness, calorificValue, storageLife);
		this.packing = packing;
		this.storageConstraints = storageConstraints;
		this.transportationConstraints = transportationConstraints;
		this.ferments = new ArrayList<String>(ferments);
		this.microElements = new ArrayList<String>(microElements);
	}

	public List<String> getFerments() {
		return ferments;
	}

	public ArrayList<String> getMicroElements() {
		return microElements;
	}

	public String getPacking() {
		return packing;
	}

	public String getStorageConstraints() {
		return storageConstraints;
	}

	public String getTransportationConstraints() {
		return transportationConstraints;
	}

	public void setFerments(final ArrayList<String> ferments) {
		this.ferments = ferments;
	}

	public void setMicroElements(final ArrayList<String> microElements) {
		this.microElements = microElements;
	}

	public void setPacking(final String packing) {
		this.packing = packing;
	}

	public void setStorageConstraints(final String storageConstraints) {
		this.storageConstraints = storageConstraints;
	}

	public void setTransportationConstraints(
			final String transportationConstraints) {
		this.transportationConstraints = transportationConstraints;
	}

	@Override
	public void validate() throws ValidationError {
		final HashMap<Enum<? extends Validatable.Fields>, String> errors = new HashMap<Enum<? extends Validatable.Fields>, String>();

		if (!Validator.validateFloat(getCalorificValue(), 0f, 1000000000f)) {
			errors.put(Fields.calorificValue,
					"Введите положительное вещественное число");
		}

		if (!Validator.validateFloat(getFatness(), 0f, 100f)) {
			errors
					.put(Fields.fatness,
							"Введите вещественное число от 0 до 100");
		}

		if (!ValidWordList(getFerments())) {
			errors.put(Fields.ferments,
					"Список непустых слов. Пробелы недопустимы");
		}

		if (!ValidWordList(getMicroElements())) {
			errors.put(Fields.microElements,
					"Список непустых слов. Пробелы недопустимы");
		}

		if (!Validator.validateString(getName(), 1, 50)) {
			errors.put(Fields.name, "Строка от 1 до 50 символов");
		}

		if (!Validator.validateString(getPacking(), 0, 50)) {
			errors.put(Fields.packing, "Строка от 0 до 50 символов");
		}

		if (!Validator.validateString(getStorageConstraints(), 0, 300)) {
			errors
					.put(Fields.storageConstraints,
							"Строка от 0 до 300 символов");
		}

		if (!Validator.validateString(getTransportationConstraints(), 0, 300)) {
			errors.put(Fields.transportationConstraints,
					"Строка от 0 до 300 символов");

		}

		if (!Validator.validateTimeSpan(getStorageLife(), 0, 86400 * 365 * 10)) {
			errors
					.put(Fields.storageLife,
							"Срок хранения должен быть положительным и не более 10 лет");

		}

		if (!errors.isEmpty()) {
			throw new ValidationError(errors);
		}
	}

	private boolean ValidWordList(final List<String> words) {
		for (final String word : words) {
			if (!Validator.validateWord(word)) {
				return false;
			}
		}

		return true;
	}
}
