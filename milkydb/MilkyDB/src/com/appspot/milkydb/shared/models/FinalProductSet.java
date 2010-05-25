package com.appspot.milkydb.shared.models;

import java.util.Date;

import com.googlecode.objectify.Key;

public class FinalProductSet extends ProductSet {

	private Key<FinalProductClass> productClass;

	/**
	 * 
	 */
	public FinalProductSet() {
		super();
	}

	/**
	 * @param manufacturingDate
	 * @param expirationDate
	 */
	public FinalProductSet(final Date manufacturingDate,
			final Date expirationDate) {
		super(manufacturingDate, expirationDate);
	}

	public Key<FinalProductClass> getProductClass() {
		return productClass;
	}

	public void setProductClass(final Key<FinalProductClass> productClass) {
		this.productClass = productClass;
	}

}
