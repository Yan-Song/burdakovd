package com.appspot.milkydb.server.services;

import com.appspot.milkydb.client.validation.ValidationError;
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
	protected Model doSave(final BaseProductClass dto, final Objectify ofy)
			throws ValidationError {
		for (final String microElement : dto.getMicroElements()) {
			DAO.getOrCreate(MicroElement.class, ofy, microElement);
		}

		for (final String ferment : dto.getFerments()) {
			DAO.getOrCreate(Ferment.class, ofy, ferment);
		}

		return super.doSave(dto, ofy);
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
