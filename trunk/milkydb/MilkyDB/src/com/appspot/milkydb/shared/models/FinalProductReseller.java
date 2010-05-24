package com.appspot.milkydb.shared.models;

import java.util.ArrayList;
import java.util.List;

import com.appspot.milkydb.shared.Model;
import com.googlecode.objectify.Key;

@SuppressWarnings("serial")
public class FinalProductReseller extends Partner implements Model {
	private List<Key<Demand>> demands = new ArrayList<Key<Demand>>();

	public List<Key<Demand>> getDemands() {
		return demands;
	}

	public void setDemands(final List<Key<Demand>> demands) {
		this.demands = demands;
	}
}
