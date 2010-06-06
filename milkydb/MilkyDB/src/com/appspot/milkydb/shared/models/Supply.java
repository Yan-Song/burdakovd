package com.appspot.milkydb.shared.models;

import com.appspot.milkydb.shared.Model;
import com.appspot.milkydb.shared.Validatable;
import com.appspot.milkydb.shared.dto.Dto;
import com.googlecode.objectify.Key;

@SuppressWarnings("serial")
public class Supply extends Contract implements Dto, Model, Validatable {

	private Key<RawMaterialClass> materialClass;

	private Key<RawMaterialProvider> provider;

	/**
	 * 
	 */
	public Supply() {
		super();
	}

	/**
	 * @param materialClass
	 * @param provider
	 */
	public Supply(final Key<RawMaterialClass> materialClass,
			final Key<RawMaterialProvider> provider) {
		this.materialClass = materialClass;
		this.provider = provider;
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
