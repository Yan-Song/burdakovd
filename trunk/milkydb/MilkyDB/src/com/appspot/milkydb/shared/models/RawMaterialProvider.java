package com.appspot.milkydb.shared.models;

import java.util.ArrayList;
import java.util.List;

import com.appspot.milkydb.shared.Model;
import com.appspot.milkydb.shared.dto.Dto;
import com.googlecode.objectify.Key;

@SuppressWarnings("serial")
public class RawMaterialProvider extends Partner implements Dto, Model {
	private List<Key<Supply>> supplies = new ArrayList<Key<Supply>>();

	public List<Key<Supply>> getSupplies() {
		return supplies;
	}

	public void setSupplies(final List<Key<Supply>> supplies) {
		this.supplies = supplies;
	}
}
