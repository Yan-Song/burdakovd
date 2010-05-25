package com.appspot.milkydb.shared.models;

import java.util.Date;

import javax.persistence.Id;

import com.appspot.milkydb.shared.HasKey;
import com.appspot.milkydb.shared.HasParent;
import com.googlecode.objectify.Key;
import com.googlecode.objectify.annotation.Parent;

public class ProductSet implements HasParent, HasKey<Long> {
	@Id
	private Long key;

	@Parent
	private Key<?> parent;

	private Date manufacturingDate = new Date();

	private Date expirationDate = new Date();

	/**
	 * 
	 */
	public ProductSet() {
	}

	/**
	 * @param manufacturingDate
	 * @param expirationDate
	 */
	public ProductSet(final Date manufacturingDate, final Date expirationDate) {
		this.manufacturingDate = manufacturingDate;
		this.expirationDate = expirationDate;
	}

	public Date getExpirationDate() {
		return expirationDate;
	}

	public Long getKey() {
		return key;
	}

	public Date getManufacturingDate() {
		return manufacturingDate;
	}

	public Key<?> getParent() {
		return parent;
	}

	public void setExpirationDate(final Date expirationDate) {
		this.expirationDate = expirationDate;
	}

	public void setKey(final Long key) {
		this.key = key;
	}

	public void setManufacturingDate(final Date manufacturingDate) {
		this.manufacturingDate = manufacturingDate;
	}

	public void setParent(final Key<?> parent) {
		this.parent = parent;
	}
}
