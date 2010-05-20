package com.appspot.milkydb.server.models;

import java.io.Serializable;
import java.util.List;

import javax.jdo.annotations.Element;
import javax.jdo.annotations.IdentityType;
import javax.jdo.annotations.PersistenceCapable;
import javax.jdo.annotations.Persistent;

import com.appspot.milkydb.shared.dto.HasKey;
import com.google.appengine.api.datastore.Key;

@SuppressWarnings("serial")
@PersistenceCapable(identityType = IdentityType.APPLICATION)
public class RawMaterialProvider extends Partner implements Serializable,
		HasKey<Key> {
	@Persistent(mappedBy = "provider")
	@Element(dependent = "true")
	private List<Supply> supplies;

	public List<Supply> getSupplies() {
		return supplies;
	}
}
