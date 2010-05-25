package com.appspot.milkydb.shared.models;

import java.util.HashSet;
import java.util.Set;

import com.appspot.milkydb.shared.HasRelations;
import com.googlecode.objectify.Key;

@SuppressWarnings("serial")
public class RawMaterialClass extends BaseProductClass implements HasRelations {
	private Set<Key<RawMaterialSet>> inStorage = new HashSet<Key<RawMaterialSet>>();
	private Set<Key<Supply>> contracts = new HashSet<Key<Supply>>();

	/**
	 * 
	 */
	public RawMaterialClass() {
		super();
	}

	/**
	 * @param key
	 * @param name
	 * @param fatness
	 * @param calorificValue
	 * @param storageLife
	 * @param packing
	 * @param storageConstraints
	 * @param transportationConstraints
	 * @param ferments
	 * @param microElements
	 */
	public RawMaterialClass(final Long key, final String name,
			final Float fatness, final Float calorificValue,
			final TimeSpan storageLife, final String packing,
			final String storageConstraints,
			final String transportationConstraints, final Set<String> ferments,
			final Set<String> microElements) {
		super(key, name, fatness, calorificValue, storageLife, packing,
				storageConstraints, transportationConstraints, ferments,
				microElements);
	}

	public Set<Key<Supply>> getContracts() {
		return contracts;
	}

	public Set<Key<RawMaterialSet>> getInStorage() {
		return inStorage;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see com.appspot.milkydb.shared.HasRelations#hasRelations()
	 */
	@Override
	public boolean hasRelations() {
		return !inStorage.isEmpty() || !contracts.isEmpty();
	}

	public void setContracts(final Set<Key<Supply>> contracts) {
		this.contracts = contracts;
	}

	public void setInStorage(final Set<Key<RawMaterialSet>> inStorage) {
		this.inStorage = inStorage;
	}
}
