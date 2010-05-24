package com.appspot.milkydb.shared.models;

import com.googlecode.objectify.Key;

public class Demand extends Contract {

	private Key<FinalProductClass> productClass;

	private Key<FinalProductReseller> reseller;

	/**
	 * 
	 */
	public Demand() {
		super();
	}

	public Key<FinalProductClass> getProductClass() {
		return productClass;
	}

	public Key<FinalProductReseller> getReseller() {
		return reseller;
	}

	public void setProductClass(final Key<FinalProductClass> productClass) {
		this.productClass = productClass;
	}

	public void setReseller(final Key<FinalProductReseller> reseller) {
		this.reseller = reseller;
	}

}
