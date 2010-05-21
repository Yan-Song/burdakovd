package com.appspot.milkydb.shared.dto;

import java.util.ArrayList;

@SuppressWarnings("serial")
public class EncodedKeys extends ArrayList<String> implements Dto {

	public EncodedKeys() {
		super();
	}

	public EncodedKeys(final ArrayList<String> keys) {
		super(keys);
	}
}
