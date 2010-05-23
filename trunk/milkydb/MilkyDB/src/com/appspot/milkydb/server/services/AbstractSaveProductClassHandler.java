package com.appspot.milkydb.server.services;

import com.appspot.milkydb.shared.models.BaseProductClass;

public class AbstractSaveProductClassHandler<Model extends BaseProductClass>
		extends AbstractSaveEntityHandler<Model, BaseProductClass> {

	public AbstractSaveProductClassHandler(final Class<Model> modelClass) {
		super(modelClass);
	}

	@Override
	protected void setData(final Model model, final BaseProductClass dto) {
		model.setCalorificValue(dto.getCalorificValue());
		model.setFatness(dto.getFatness());
		model.setFerments(dto.getFerments());
		model.setMicroElements(dto.getMicroElements());
		model.setName(dto.getName());
		model.setPacking(dto.getPacking());
		model.setStorageConstraints(dto.getStorageConstraints());
		model.setStorageLife(dto.getStorageLife());
		model.setTransportationConstraints(dto.getTransportationConstraints());
	}

}
