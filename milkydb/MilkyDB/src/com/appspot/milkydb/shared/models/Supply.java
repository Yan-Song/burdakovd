package com.appspot.milkydb.shared.models;

import com.appspot.milkydb.shared.dto.Dto;
import com.googlecode.objectify.Key;

@SuppressWarnings("serial")
public class Supply extends Contract implements Dto {

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
