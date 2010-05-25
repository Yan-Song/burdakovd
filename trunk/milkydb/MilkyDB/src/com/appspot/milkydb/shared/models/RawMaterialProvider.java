package com.appspot.milkydb.shared.models;

import java.util.HashSet;
import java.util.Set;

import com.appspot.milkydb.shared.HasRelations;
import com.appspot.milkydb.shared.Model;
import com.appspot.milkydb.shared.dto.Dto;
import com.googlecode.objectify.Key;

@SuppressWarnings("serial")
public class RawMaterialProvider extends Partner implements Dto, Model,
		HasRelations {
	private Set<Key<Supply>> supplies = new HashSet<Key<Supply>>();
	private Set<Key<RawMaterialSet>> inStorage = new HashSet<Key<RawMaterialSet>>();

	/**
	 * 
	 */
	public RawMaterialProvider() {
		super();
	}

	/**
	 * @param name
	 * @param contactInfo
	 */
	public RawMaterialProvider(final String name, final ContactInfo contactInfo) {
		super(name, contactInfo);
	}

	public Set<Key<RawMaterialSet>> getInStorage() {
		return inStorage;
	}

	public Set<Key<Supply>> getSupplies() {
		return supplies;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see com.appspot.milkydb.shared.HasRelations#hasRelations()
	 */
	@Override
	public boolean hasRelations() {
		return !supplies.isEmpty() || !inStorage.isEmpty();
	}

	public void setInStorage(final Set<Key<RawMaterialSet>> inStorage) {
		this.inStorage = inStorage;
	}

	public void setSupplies(final Set<Key<Supply>> supplies) {
		this.supplies = supplies;
	}
}
