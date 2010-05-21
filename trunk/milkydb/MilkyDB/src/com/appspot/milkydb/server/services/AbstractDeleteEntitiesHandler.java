package com.appspot.milkydb.server.services;

import javax.jdo.PersistenceManager;

import com.appspot.milkydb.client.validation.ValidationError;
import com.appspot.milkydb.server.PMF;
import com.appspot.milkydb.shared.dto.EncodedKey;
import com.appspot.milkydb.shared.dto.EncodedKeys;
import com.appspot.milkydb.shared.dto.RpcVoid;
import com.google.appengine.api.datastore.KeyFactory;

public class AbstractDeleteEntitiesHandler<Model> implements
		ActionHandler<EncodedKeys, RpcVoid> {

	private final Class<Model> modelClass;

	public AbstractDeleteEntitiesHandler(final Class<Model> modelClass) {
		this.modelClass = modelClass;
	}

	private void doDelete(final PersistenceManager pm, final EncodedKeys keys) {
		for (final EncodedKey key : keys) {
			pm.deletePersistent(pm.getObjectById(modelClass, KeyFactory
					.stringToKey(key.getValue())));
		}
	}

	@Override
	public RpcVoid execute(final EncodedKeys keys) throws ValidationError {

		final PersistenceManager pm = PMF.get();

		try {
			doDelete(pm, keys);
			return null;
		} finally {
			pm.close();
		}
	}

}
