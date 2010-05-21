package com.appspot.milkydb.server.services;

import com.appspot.milkydb.server.models.BaseProductClass;
import com.appspot.milkydb.shared.dto.EncodedKey;
import com.appspot.milkydb.shared.dto.FullProductClass;
import com.google.appengine.api.datastore.KeyFactory;

public class AbstractGetProductClassHandler<Model extends BaseProductClass>
		extends AbstractGetEntityHandler<Model, FullProductClass> {

	public AbstractGetProductClassHandler(final Class<Model> modelClass) {
		super(modelClass);
	}

	@Override
	protected FullProductClass makeDto(final Model model) {
		return new FullProductClass(new EncodedKey(KeyFactory.keyToString(model
				.getKey())), model.getName(), model.getFatness(), model
				.getCalorificValue(), model.getStorageLife(), model
				.getPacking(), model.getStorageConstraints().getValue(), model
				.getTransportationConstraints().getValue(),
				model.getFerments(), model.getMicroElements());
	}
}
