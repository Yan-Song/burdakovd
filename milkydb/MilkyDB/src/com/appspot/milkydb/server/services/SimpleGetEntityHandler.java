package com.appspot.milkydb.server.services;

import com.appspot.milkydb.shared.Model;
import com.appspot.milkydb.shared.dto.Dto;
import com.appspot.milkydb.shared.dto.SingleKey;

public class SimpleGetEntityHandler<M extends Dto & Model> extends
		AbstractGetEntityHandler<M, M> implements ActionHandler<SingleKey, M> {

	public SimpleGetEntityHandler(final Class<M> modelClass) {
		super(modelClass);
	}

	@Override
	protected M makeDto(final M model) {
		return model;
	}
}
