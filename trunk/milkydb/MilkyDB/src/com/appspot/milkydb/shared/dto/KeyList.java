package com.appspot.milkydb.shared.dto;

import java.util.ArrayList;
import java.util.Collection;

@SuppressWarnings("serial")
public class KeyList extends ArrayList<SingleKey> implements Dto {

	public KeyList() {
		super();
	}

	public KeyList(final ArrayList<SingleKey> keys) {
		super(keys);
	}

	public KeyList(final Collection<? extends SingleKey> c) {
		super(c);
	}
}
