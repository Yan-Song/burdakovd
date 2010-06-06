package com.appspot.milkydb.shared.models;

import javax.persistence.Id;

import com.appspot.milkydb.client.validation.ValidationError;
import com.appspot.milkydb.client.validation.Validator;
import com.appspot.milkydb.shared.HasKey;
import com.appspot.milkydb.shared.HasParent;
import com.appspot.milkydb.shared.Validatable;
import com.appspot.milkydb.shared.dto.Dto;
import com.googlecode.objectify.Key;
import com.googlecode.objectify.annotation.Parent;

@SuppressWarnings("serial")
public abstract class Contract implements HasKey<Long>, HasParent, Validatable,
		Dto {

	public static enum Fields implements Validatable.Fields {
		frequency, count
	}

	@Id
	private Long key;

	@Parent
	private Key<?> parent;

	private TimeSpan frequency = new TimeSpan(0);

	private Integer count = new Integer(0);

	/**
	 * 
	 */
	public Contract() {
	}

	public Integer getCount() {
		return count;
	}

	public TimeSpan getFrequency() {
		return frequency;
	}

	public Long getKey() {
		return key;
	}

	public Key<?> getParent() {
		return parent;
	}

	public void setCount(final Integer count) {
		this.count = count;
	}

	public void setFrequency(final TimeSpan frequency) {
		this.frequency = frequency;
	}

	public void setKey(final Long key) {
		this.key = key;
	}

	public void setParent(final Key<?> parent) {
		this.parent = parent;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see com.appspot.milkydb.shared.Validatable#validate()
	 */
	@Override
	public void validate() throws ValidationError {
		if (!Validator.validateInteger(count, 1, 1000000)) {
			throw new ValidationError(Fields.count, "");
		}

		if (!Validator.validateTimeSpan(frequency, 0, 86400 * 365 * 10)) {
			throw new ValidationError(Fields.frequency, "");
		}
	}
}
