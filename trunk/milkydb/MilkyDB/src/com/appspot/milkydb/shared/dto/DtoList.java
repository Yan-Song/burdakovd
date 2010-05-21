package com.appspot.milkydb.shared.dto;

import java.util.ArrayList;
import java.util.List;

@SuppressWarnings("serial")
public class DtoList<Model extends Dto> extends ArrayList<Model> implements Dto {

	public DtoList() {
		super();
	}

	public DtoList(final List<Model> l) {
		super(l);
	}
}
