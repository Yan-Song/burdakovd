package com.appspot.milkydb.server.models;

import javax.jdo.annotations.IdentityType;
import javax.jdo.annotations.PersistenceCapable;
import javax.jdo.annotations.Persistent;

import com.appspot.milkydb.shared.models.FinalProductClass;
import com.appspot.milkydb.shared.models.FinalProductReseller;

@PersistenceCapable(identityType = IdentityType.APPLICATION)
public class FinalProductSet extends ProductSet {
	@Persistent
	private FinalProductClass productClass;

	@Persistent
	private FinalProductReseller reseller;

	public FinalProductClass getProductClass() {
		return productClass;
	}

	public FinalProductReseller getReseller() {
		return reseller;
	}

	public void setProductClass(final FinalProductClass productClass) {
		this.productClass = productClass;
	}

	public void setReseller(final FinalProductReseller reseller) {
		this.reseller = reseller;
	}
}
