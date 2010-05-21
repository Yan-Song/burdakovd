package com.appspot.milkydb.server.services;

import javax.jdo.PersistenceManager;

import com.appspot.milkydb.server.PMF;
import com.appspot.milkydb.shared.dto.Dto;
import com.appspot.milkydb.shared.dto.EncodedKey;
import com.google.appengine.api.datastore.KeyFactory;

public abstract class AbstractGetEntityHandler<Model, FullDto extends Dto>
		implements ActionHandler<EncodedKey, FullDto> {

	private final Class<Model> modelClass;

	public AbstractGetEntityHandler(final Class<Model> modelClass) {
		this.modelClass = modelClass;
	}

	private FullDto doGet(final PersistenceManager pm,
			final EncodedKey encodedKey) {
		final Model model = pm.getObjectById(modelClass, KeyFactory
				.stringToKey(encodedKey.getKey()));
		return makeDto(model);
	}

	@Override
	public FullDto execute(final EncodedKey request) {
		final PersistenceManager pm = PMF.get();

		try {
			return doGet(pm, request);
		} finally {
			pm.close();
		}
	}

	/*
	 * наследующие классы должны создавать здесь DTO из модели
	 */
	protected abstract FullDto makeDto(Model model);
}
