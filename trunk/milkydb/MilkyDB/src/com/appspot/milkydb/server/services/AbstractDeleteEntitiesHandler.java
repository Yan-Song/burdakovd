package com.appspot.milkydb.server.services;

import java.util.ArrayList;

import javax.jdo.PersistenceManager;

import com.appspot.milkydb.client.validation.ValidationException;
import com.appspot.milkydb.server.PMF;
import com.appspot.milkydb.shared.dto.SerializableVoid;
import com.google.appengine.api.datastore.KeyFactory;

public class AbstractDeleteEntitiesHandler<Model> implements
		ActionHandler<ArrayList<String>, SerializableVoid> {

	private final Class<Model> modelClass;

	public AbstractDeleteEntitiesHandler(final Class<Model> modelClass) {
		this.modelClass = modelClass;
	}

	private void doDelete(final PersistenceManager pm,
			final ArrayList<String> keys) {
		for (final String key : keys) {
			pm.deletePersistent(pm.getObjectById(modelClass, KeyFactory
					.stringToKey(key)));
		}
	}

	@Override
	public SerializableVoid execute(final ArrayList<String> keys)
			throws ValidationException {

		final PersistenceManager pm = PMF.get();

		try {
			doDelete(pm, keys);
			return null;
		} finally {
			pm.close();
		}
	}

}
