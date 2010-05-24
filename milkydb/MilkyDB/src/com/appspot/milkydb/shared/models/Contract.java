package com.appspot.milkydb.shared.models;

import javax.persistence.Id;

import com.appspot.milkydb.shared.HasKey;
import com.googlecode.objectify.Key;
import com.googlecode.objectify.annotation.Parent;

public class Contract implements HasKey<Long> {
	@Id
	private Long key;

	@Parent
	private Key<?> owner;

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

	public Key<?> getOwner() {
		return owner;
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

	public void setOwner(final Key<?> owner) {
		this.owner = owner;
	}

}
