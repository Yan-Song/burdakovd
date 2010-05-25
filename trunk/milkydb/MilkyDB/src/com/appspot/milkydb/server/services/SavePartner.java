package com.appspot.milkydb.server.services;

import com.appspot.milkydb.shared.Model;
import com.appspot.milkydb.shared.dto.SingleKey;
import com.appspot.milkydb.shared.models.Partner;
import com.googlecode.objectify.Objectify;

public class SavePartner<M extends Partner & Model> extends
		AbstractSaveEntityHandler<M, Partner> implements
		ActionHandler<Partner, SingleKey> {

	public SavePartner(final Class<M> modelClass) {
		super(modelClass);
	}

	@Override
	protected void setData(final Objectify ofy, final M model, final Partner dto) {
		model.setContactInfo(dto.getContactInfo());
		model.setName(dto.getName());
	}

}
