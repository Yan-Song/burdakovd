package com.appspot.milkydb.server.services;

import com.appspot.milkydb.client.validation.ValidationError;
import com.appspot.milkydb.server.DAO;
import com.appspot.milkydb.shared.Model;
import com.appspot.milkydb.shared.Validatable;
import com.appspot.milkydb.shared.dto.KeyList;
import com.appspot.milkydb.shared.dto.RpcVoid;
import com.appspot.milkydb.shared.dto.SingleKey;
import com.google.appengine.repackaged.com.google.common.base.Function;
import com.google.appengine.repackaged.com.google.common.collect.Iterables;
import com.googlecode.objectify.Key;
import com.googlecode.objectify.Objectify;

public class SimpleDeleteEntitiesHandler<M extends Model> implements
		ActionHandler<KeyList, RpcVoid> {

	@SuppressWarnings("serial")
	static class CanNotDeleteException extends ValidationError {
		public CanNotDeleteException(final String why) {
			super(Validatable.Delete.canNotDelete, why);
		}
	}

	private final Class<M> modelClass;

	public SimpleDeleteEntitiesHandler(final Class<M> modelClass) {
		this.modelClass = modelClass;
	}

	protected void beforeDelete(final DAO dao, final Objectify ofy,
			final Iterable<Key<M>> tKeys) {
	}

	/**
	 * Эта функция должна проверять, можем ли мы удалить объекты с указанными
	 * ключами, и если не можем - выбрасывать исключение с причиной. Функция
	 * будет запускаться внутри транзакции.
	 * 
	 * @param dao
	 * @param t
	 * @param tKeys
	 * @throws CanNotDeleteException
	 */
	protected void checkIfCanDelete(final DAO dao, final Objectify t,
			final Iterable<Key<M>> tKeys) throws CanNotDeleteException {
	}

	@Override
	public RpcVoid execute(final KeyList keys) throws ValidationError {

		final DAO dao = new DAO();

		final Objectify t = dao.fact().beginTransaction();

		try {

			final Iterable<Key<M>> tKeys = Iterables.transform(keys,
					new Function<SingleKey, Key<M>>() {
						@Override
						public Key<M> apply(final SingleKey single) {
							return new Key<M>(DAO.rootKey, modelClass, single
									.getValue());
						}
					});

			checkIfCanDelete(dao, t, tKeys);

			beforeDelete(dao, t, tKeys);

			t.delete(tKeys);

			t.getTxn().commit();

			return null;

		} finally {
			if (t.getTxn().isActive()) {
				t.getTxn().rollback();
			}
		}
	}
}
