package com.appspot.milkydb.server.services;

import com.appspot.milkydb.shared.models.BaseProductClass;

public class GetProductClassHandler<Model extends BaseProductClass> extends
		AbstractGetEntityHandler<Model, BaseProductClass> {

	public GetProductClassHandler(final Class<Model> modelClass) {
		super(modelClass);
	}

	@Override
	protected BaseProductClass makeDto(final Model model) {
		return model;
	}
}
