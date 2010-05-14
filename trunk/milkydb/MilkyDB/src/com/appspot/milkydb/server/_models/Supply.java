package com.appspot.milkydb.server._models;

import javax.jdo.annotations.IdentityType;
import javax.jdo.annotations.PersistenceCapable;
import javax.jdo.annotations.Persistent;

@PersistenceCapable(identityType = IdentityType.APPLICATION)
public class Supply extends Contract {
	@Persistent
	private RawMaterialClass materialClass;

	@Persistent
	private RawMaterialProvider provider;

	public RawMaterialClass getMaterialClass() {
		return materialClass;
	}

	public RawMaterialProvider getProvider() {
		return provider;
	}

	public void setMaterialClass(final RawMaterialClass materialClass) {
		this.materialClass = materialClass;
	}

	public void setProvider(final RawMaterialProvider provider) {
		this.provider = provider;
	}
}
