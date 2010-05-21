package com.appspot.milkydb.shared.dto;

import java.util.ArrayList;

@SuppressWarnings("serial")
public class EncodedKeys extends ArrayList<EncodedKey> implements Dto {

	public EncodedKeys() {
		super();
	}

	public EncodedKeys(final ArrayList<EncodedKey> keys) {
		super(keys);
	}
}
