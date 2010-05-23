package com.appspot.milkydb.server.services;

import com.appspot.milkydb.client.validation.ValidationError;
import com.appspot.milkydb.server.DAO;
import com.appspot.milkydb.shared.Model;
import com.appspot.milkydb.shared.dto.KeyList;
import com.appspot.milkydb.shared.dto.RpcVoid;
import com.appspot.milkydb.shared.dto.SingleKey;
import com.google.appengine.repackaged.com.google.common.base.Function;
import com.google.appengine.repackaged.com.google.common.collect.Iterables;
import com.googlecode.objectify.Key;

public class AbstractDeleteEntitiesHandler<M extends Model> implements
		ActionHandler<KeyList, RpcVoid> {

	private final Class<M> modelClass;

	public AbstractDeleteEntitiesHandler(final Class<M> modelClass) {
		this.modelClass = modelClass;
	}

	@Override
	public RpcVoid execute(final KeyList keys) throws ValidationError {

		final DAO dao = new DAO();

		dao.ofy().delete(
				Iterables.transform(keys, new Function<SingleKey, Key<M>>() {
					@Override
					public Key<M> apply(final SingleKey single) {
						return new Key<M>(DAO.rootKey, modelClass, single
								.getValue());
					}
				}));

		return null;
	}
}
