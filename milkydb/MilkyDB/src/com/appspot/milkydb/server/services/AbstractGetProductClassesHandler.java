package com.appspot.milkydb.server.services;

import javax.jdo.Query;

import com.appspot.milkydb.server.models.BaseProductClass;
import com.appspot.milkydb.shared.dto.EncodedKey;
import com.appspot.milkydb.shared.dto.LightProductClass;
import com.google.appengine.api.datastore.KeyFactory;

public class AbstractGetProductClassesHandler<ProductClassModel extends BaseProductClass>
		extends
		AbstractGetEntitiesHandler<ProductClassModel, LightProductClass> {

	public AbstractGetProductClassesHandler(final Class<ProductClassModel> modelClass) {
		super(modelClass);
	}

	@Override
	protected LightProductClass makeLightDto(final ProductClassModel model) {
		return new LightProductClass(new EncodedKey(KeyFactory
				.keyToString(model.getKey())), model.getName(), model
				.getFatness(), model.getCalorificValue(), model
				.getStorageLife());
	}

	@Override
	protected void setOrdering(final Query query) {
		query.setOrdering("name asc");
	}
}
