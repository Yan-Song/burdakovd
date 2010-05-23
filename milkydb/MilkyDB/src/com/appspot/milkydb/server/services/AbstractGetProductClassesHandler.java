package com.appspot.milkydb.server.services;

import com.appspot.milkydb.shared.dto.LightProductClass;
import com.appspot.milkydb.shared.models.BaseProductClass;

public class AbstractGetProductClassesHandler<ProductClassModel extends BaseProductClass>
		extends
		AbstractGetEntitiesHandler<ProductClassModel, LightProductClass> {

	public AbstractGetProductClassesHandler(
			final Class<ProductClassModel> modelClass) {
		super(modelClass);
	}

	@Override
	protected String getOrdering() {
		return "name";
	}

	@Override
	protected LightProductClass makeLightDto(final ProductClassModel model) {
		return new LightProductClass(model.getKey(), model.getName(), model
				.getFatness(), model.getCalorificValue(), model
				.getStorageLife());
	}
}
