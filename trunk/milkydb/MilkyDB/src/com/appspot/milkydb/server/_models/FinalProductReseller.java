package com.appspot.milkydb.server._models;

import java.util.List;

import javax.jdo.annotations.Element;
import javax.jdo.annotations.IdentityType;
import javax.jdo.annotations.PersistenceCapable;
import javax.jdo.annotations.Persistent;

@PersistenceCapable(identityType = IdentityType.APPLICATION)
public class FinalProductReseller extends Partner {
	@Persistent(mappedBy = "reseller")
	@Element(dependent = "true")
	private List<Demand> demands;

	public List<Demand> getDemands() {
		return demands;
	}
}
