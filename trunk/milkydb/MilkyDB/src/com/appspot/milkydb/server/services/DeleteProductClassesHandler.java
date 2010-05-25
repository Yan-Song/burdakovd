/**
 * 
 */
package com.appspot.milkydb.server.services;

import java.util.Collection;
import java.util.HashMap;
import java.util.Map;

import com.appspot.milkydb.server.DAO;
import com.appspot.milkydb.shared.HasRelations;
import com.appspot.milkydb.shared.models.BaseProductClass;
import com.appspot.milkydb.shared.models.Ferment;
import com.appspot.milkydb.shared.models.MicroElement;
import com.googlecode.objectify.Key;
import com.googlecode.objectify.Objectify;

/**
 * @author burdakovd
 * 
 */
public class DeleteProductClassesHandler<M extends BaseProductClass & HasRelations>
		extends RelationsCheckedDeleteEntitiesHandler<M> {

	/**
	 * @param modelClass
	 */
	public DeleteProductClassesHandler(final Class<M> modelClass) {
		super(modelClass);
	}

	@Override
	protected void beforeDelete(final DAO dao, final Objectify t,
			final Iterable<Key<M>> tKeys) {

		final Collection<M> entities = t.get(tKeys).values();

		final Map<String, Integer> removedFerments = new HashMap<String, Integer>();
		final Map<String, Integer> removedMicroElements = new HashMap<String, Integer>();

		for (final M entity : entities) {
			for (final String ferment : entity.getFerments()) {
				removedFerments.put(ferment, (removedFerments
						.containsKey(ferment) ? removedFerments.get(ferment)
						: 0) + 1);
			}

			for (final String microElement : entity.getMicroElements()) {
				removedMicroElements.put(microElement, (removedMicroElements
						.containsKey(microElement) ? removedMicroElements
						.get(microElement) : 0) + 1);
			}
		}

		DAO.decrementAndDeleteIfNotUsed(t, Ferment.class, removedFerments);
		DAO.decrementAndDeleteIfNotUsed(t, MicroElement.class,
				removedMicroElements);

		super.beforeDelete(dao, t, tKeys);
	}
}
