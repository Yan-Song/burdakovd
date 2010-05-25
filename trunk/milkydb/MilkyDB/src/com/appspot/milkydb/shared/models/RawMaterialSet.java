package com.appspot.milkydb.shared.models;

import java.util.Date;

import com.googlecode.objectify.Key;

public class RawMaterialSet extends ProductSet {

	private Key<RawMaterialClass> materialClass;

	private Key<RawMaterialProvider> provider;

	/**
	 * 
	 */
	public RawMaterialSet() {
		super();
	}

	/**
	 * @param manufacturingDate
	 * @param expirationDate
	 */
	public RawMaterialSet(final Date manufacturingDate,
			final Date expirationDate) {
		super(manufacturingDate, expirationDate);
	}

	public Key<RawMaterialClass> getMaterialClass() {
		return materialClass;
	}

	public Key<RawMaterialProvider> getProvider() {
		return provider;
	}

	public void setMaterialClass(final Key<RawMaterialClass> materialClass) {
		this.materialClass = materialClass;
	}

	public void setProvider(final Key<RawMaterialProvider> provider) {
		this.provider = provider;
	}

}
