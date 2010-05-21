package com.appspot.milkydb.server.services;

import com.appspot.milkydb.server.models.BaseProductClass;
import com.appspot.milkydb.shared.dto.FullProductClass;
import com.google.appengine.api.datastore.Text;

public class AbstractSaveProductClassHandler<Model extends BaseProductClass> extends
		AbstractSaveEntityHandler<Model, FullProductClass> {

	public AbstractSaveProductClassHandler(final Class<Model> modelClass) {
		super(modelClass);
	}

	@Override
	protected void setData(final Model model, final FullProductClass dto) {
		model.setCalorificValue(dto.getCalorificValue());
		model.setFatness(dto.getFatness());
		model.setFerments(dto.getFerments());
		model.setMicroElements(dto.getMicroElements());
		model.setName(dto.getName());
		model.setPacking(dto.getPacking());
		model.setStorageConstraints(new Text(dto.getStorageConstraints()));
		model.setStorageLife(dto.getStorageLife());
		model.setTransportationConstraints(new Text(dto
				.getTransportationConstraints()));
	}

}
