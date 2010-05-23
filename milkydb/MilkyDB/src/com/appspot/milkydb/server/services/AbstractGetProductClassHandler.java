package com.appspot.milkydb.server.services;

import com.appspot.milkydb.shared.models.BaseProductClass;

public class AbstractGetProductClassHandler<Model extends BaseProductClass>
		extends AbstractGetEntityHandler<Model, BaseProductClass> {

	public AbstractGetProductClassHandler(final Class<Model> modelClass) {
		super(modelClass);
	}

	@Override
	protected BaseProductClass makeDto(final Model model) {
		return model;
	}
}
