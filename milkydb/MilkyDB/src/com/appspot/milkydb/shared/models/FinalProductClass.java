package com.appspot.milkydb.shared.models;

import java.util.HashSet;
import java.util.Set;

import com.appspot.milkydb.shared.HasRelations;
import com.googlecode.objectify.Key;

@SuppressWarnings("serial")
public class FinalProductClass extends BaseProductClass implements HasRelations {
	private Set<Key<Demand>> contracts = new HashSet<Key<Demand>>();
	private Set<Key<FinalProductSet>> inStorage = new HashSet<Key<FinalProductSet>>();

	/**
	 * 
	 */
	public FinalProductClass() {
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
	public FinalProductClass(final Long key, final String name,
			final Float fatness, final Float calorificValue,
			final TimeSpan storageLife, final String packing,
			final String storageConstraints,
			final String transportationConstraints, final Set<String> ferments,
			final Set<String> microElements) {
		super(key, name, fatness, calorificValue, storageLife, packing,
				storageConstraints, transportationConstraints, ferments,
				microElements);
	}

	public Set<Key<Demand>> getContracts() {
		return contracts;
	}

	public Set<Key<FinalProductSet>> getInStorage() {
		return inStorage;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see com.appspot.milkydb.shared.HasRelations#hasRelations()
	 */
	@Override
	public boolean hasRelations() {
		return !contracts.isEmpty() || !inStorage.isEmpty();
	}

	public void setContracts(final Set<Key<Demand>> contracts) {
		this.contracts = contracts;
	}

	public void setInStorage(final Set<Key<FinalProductSet>> inStorage) {
		this.inStorage = inStorage;
	}
}
