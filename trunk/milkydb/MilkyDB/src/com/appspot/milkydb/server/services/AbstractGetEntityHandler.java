package com.appspot.milkydb.server.services;

import java.io.Serializable;

import javax.jdo.PersistenceManager;

import com.appspot.milkydb.server.PMF;
import com.google.appengine.api.datastore.KeyFactory;

public abstract class AbstractGetEntityHandler<Model, Dto extends Serializable>
		implements ActionHandler<String, Dto> {

	private final Class<Model> modelClass;

	public AbstractGetEntityHandler(final Class<Model> modelClass) {
		this.modelClass = modelClass;
	}

	@Override
	public Dto execute(final String request) {
		final PersistenceManager pm = PMF.get();

		try {
			return doGet(pm, request);
		} finally {
			pm.close();
		}
	}

	private Dto doGet(final PersistenceManager pm, final String request) {
		final Model model = pm.getObjectById(modelClass, KeyFactory
				.stringToKey(request));
		return makeDto(model);
	}

	/*
	 * наследующие классы должны создавать здесь DTO из модели
	 */
	protected abstract Dto makeDto(Model model);
}
