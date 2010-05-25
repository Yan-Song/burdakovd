/**
 * 
 */
package com.appspot.milkydb.server.services;

import java.util.Collection;

import com.appspot.milkydb.server.DAO;
import com.appspot.milkydb.shared.HasRelations;
import com.appspot.milkydb.shared.Model;
import com.googlecode.objectify.Key;
import com.googlecode.objectify.Objectify;

/**
 * @author burdakovd
 * 
 */
public class RelationsCheckedDeleteEntitiesHandler<M extends Model & HasRelations>
		extends SimpleDeleteEntitiesHandler<M> {

	/**
	 * @param modelClass
	 */
	public RelationsCheckedDeleteEntitiesHandler(final Class<M> modelClass) {
		super(modelClass);
	}

	@Override
	protected void checkIfCanDelete(final DAO dao, final Objectify t,
			final Iterable<Key<M>> tKeys)
			throws com.appspot.milkydb.server.services.SimpleDeleteEntitiesHandler.CanNotDeleteException {
		super.checkIfCanDelete(dao, t, tKeys);

		final Collection<M> entities = t.get(tKeys).values();

		for (final M entity : entities) {
			if (entity.hasRelations()) {
				throw new CanNotDeleteException(
						"Невозможно удалить '"
								+ entity.toString()
								+ "', в хранилище ещё есть ссылки на него, нужно сначала удалить ссылающиеся объекты");
			}
		}
	}

}
