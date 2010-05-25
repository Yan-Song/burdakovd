package com.appspot.milkydb.shared.models;

import java.util.HashSet;
import java.util.Set;

import com.appspot.milkydb.shared.HasRelations;
import com.appspot.milkydb.shared.Model;
import com.googlecode.objectify.Key;

@SuppressWarnings("serial")
public class FinalProductReseller extends Partner implements Model,
		HasRelations {
	private Set<Key<Demand>> demands = new HashSet<Key<Demand>>();

	public Set<Key<Demand>> getDemands() {
		return demands;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see com.appspot.milkydb.shared.HasRelations#hasRelations()
	 */
	@Override
	public boolean hasRelations() {
		return !demands.isEmpty();
	}

	public void setDemands(final Set<Key<Demand>> demands) {
		this.demands = demands;
	}
}
