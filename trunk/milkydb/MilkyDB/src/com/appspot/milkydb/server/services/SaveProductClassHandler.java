package com.appspot.milkydb.server.services;

import com.appspot.milkydb.server.DAO;
import com.appspot.milkydb.shared.models.BaseProductClass;
import com.appspot.milkydb.shared.models.Ferment;
import com.appspot.milkydb.shared.models.MicroElement;
import com.googlecode.objectify.Objectify;

public class SaveProductClassHandler<Model extends BaseProductClass> extends
		AbstractSaveEntityHandler<Model, BaseProductClass> {

	public SaveProductClassHandler(final Class<Model> modelClass) {
		super(modelClass);
	}

	@Override
	protected void setData(final Objectify ofy, final Model model,
			final BaseProductClass dto) {

		DAO.updateDictionaryFields(ofy, Ferment.class, model.getFerments(), dto
				.getFerments());
		DAO.updateDictionaryFields(ofy, MicroElement.class, model
				.getMicroElements(), dto.getMicroElements());

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
