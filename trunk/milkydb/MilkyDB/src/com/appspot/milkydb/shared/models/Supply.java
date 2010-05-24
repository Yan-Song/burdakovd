package com.appspot.milkydb.shared.models;

import com.googlecode.objectify.Key;

public class Supply extends Contract {

	private Key<RawMaterialClass> materialClass;

	private Key<RawMaterialProvider> provider;

	/**
	 * 
	 */
	public Supply() {
		super();
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
