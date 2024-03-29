package com.appspot.milkydb.shared.models;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;

import javax.persistence.Embedded;
import javax.persistence.Id;

import com.appspot.milkydb.client.validation.ValidationError;
import com.appspot.milkydb.client.validation.Validator;
import com.appspot.milkydb.shared.HasKey;
import com.appspot.milkydb.shared.HasParent;
import com.appspot.milkydb.shared.Model;
import com.appspot.milkydb.shared.Validatable;
import com.appspot.milkydb.shared.dto.Dto;
import com.google.appengine.api.datastore.Text;
import com.googlecode.objectify.Key;
import com.googlecode.objectify.annotation.Parent;

@SuppressWarnings("serial")
public class BaseProductClass implements Model, HasKey<Long>, Dto, Validatable,
		HasParent {

	public enum Fields implements Validatable.Fields {
		name, fatness, calorificValue, storageLife, packing, storageConstraints, transportationConstraints, ferments, microElements
	}

	@Id
	private Long key;

	@Parent
	private Key<?> parent;

	private String name = "";

	private Float fatness = 0f;

	private Float calorificValue = 0f;

	@Embedded
	private TimeSpan storageLife = new TimeSpan(0);

	private String packing = "";

	private Text storageConstraints = new Text("");

	private Text transportationConstraints = new Text("");

	private Set<String> ferments = new HashSet<String>();

	private Set<String> microElements = new HashSet<String>();

	public BaseProductClass() {

	}

	/**
	 * @param key
	 * @param name
	 * @param fatness
	 * @param calorificValue
	 * @param storageLife
	 * @param packing
	 * @param storageConstraints
	 * @param transportationConstraints
	 * @param ferments
	 * @param microElements
	 */
	public BaseProductClass(final Long key, final String name,
			final Float fatness, final Float calorificValue,
			final TimeSpan storageLife, final String packing,
			final String storageConstraints,
			final String transportationConstraints, final Set<String> ferments,
			final Set<String> microElements) {
		this.key = key;
		this.name = name;
		this.fatness = fatness;
		this.calorificValue = calorificValue;
		this.storageLife = storageLife;
		this.packing = packing;
		this.storageConstraints = new Text(storageConstraints);
		this.transportationConstraints = new Text(transportationConstraints);
		this.ferments = ferments;
		this.microElements = microElements;
	}

	public Float getCalorificValue() {
		return calorificValue;
	}

	public Float getFatness() {
		return fatness;
	}

	public Set<String> getFerments() {
		return ferments;
	}

	public Long getKey() {
		return key;
	}

	public Set<String> getMicroElements() {
		return microElements;
	}

	public String getName() {
		return name;
	}

	public String getPacking() {
		return packing;
	}

	public Key<?> getParent() {
		return parent;
	}

	public String getStorageConstraints() {
		return storageConstraints.getValue();
	}

	public TimeSpan getStorageLife() {
		return storageLife;
	}

	public String getTransportationConstraints() {
		return transportationConstraints.getValue();
	}

	public void setCalorificValue(final Float calorificValue) {
		this.calorificValue = calorificValue;
	}

	public void setFatness(final Float fatness) {
		this.fatness = fatness;
	}

	public void setFerments(final Set<String> ferments) {
		this.ferments = ferments;
	}

	public void setKey(final Long key) {
		this.key = key;
	}

	public void setMicroElements(final Set<String> microElements) {
		this.microElements = microElements;
	}

	public void setName(final String name) {
		this.name = name;
	}

	public void setPacking(final String packing) {
		this.packing = packing;
	}

	public void setParent(final Key<?> parent) {
		this.parent = parent;
	}

	public void setStorageConstraints(final String storageConstraints) {
		this.storageConstraints = new Text(storageConstraints);
	}

	public void setStorageLife(final TimeSpan storageLife) {
		this.storageLife = storageLife;
	}

	public void setTransportationConstraints(
			final String transportationConstraints) {
		this.transportationConstraints = new Text(transportationConstraints);
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

		if (!validWords(getFerments())) {
			errors.put(Fields.ferments,
					"Список непустых слов. Пробелы недопустимы");
		}

		if (!validWords(getMicroElements())) {
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

	private boolean validWords(final Set<String> words) {
		for (final String word : words) {
			if (!Validator.validateWord(word)) {
				return false;
			}
		}

		return true;
	}
}
