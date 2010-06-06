/**
 * 
 */
package com.appspot.milkydb.server.services;

import java.util.HashMap;
import java.util.Map;

import com.appspot.milkydb.server.DAO;
import com.appspot.milkydb.shared.models.RawMaterialClass;
import com.appspot.milkydb.shared.models.RawMaterialProvider;
import com.appspot.milkydb.shared.models.Supply;
import com.googlecode.objectify.Key;
import com.googlecode.objectify.Objectify;

/**
 * @author burdakovd
 * 
 */
public class SupplyDeleteHandler extends SimpleDeleteEntitiesHandler<Supply> {

	/**
	 * @param modelClass
	 */
	public SupplyDeleteHandler() {
		super(Supply.class);
	}

	@Override
	protected void beforeDelete(final DAO dao, final Objectify ofy,
			final Iterable<Key<Supply>> tKeys) {

		final Map<Key<RawMaterialProvider>, RawMaterialProvider> providers = new HashMap<Key<RawMaterialProvider>, RawMaterialProvider>();
		final Map<Key<RawMaterialClass>, RawMaterialClass> classes = new HashMap<Key<RawMaterialClass>, RawMaterialClass>();

		for (final Map.Entry<Key<Supply>, Supply> entry : ofy.get(tKeys)
				.entrySet()) {
			final Supply supply = entry.getValue();
			final Key<Supply> key = entry.getKey();
			final Key<RawMaterialProvider> providerKey = supply.getProvider();
			final Key<RawMaterialClass> classKey = supply.getMaterialClass();
			if (!providers.containsKey(providerKey)) {
				providers.put(providerKey, ofy.get(providerKey));
			}
			if (!classes.containsKey(classKey)) {
				classes.put(classKey, ofy.get(classKey));
			}

			providers.get(providerKey).getSupplies().remove(key);
			classes.get(classKey).getContracts().remove(key);
		}

		for (final RawMaterialProvider provider : providers.values()) {
			ofy.put(provider);
		}

		for (final RawMaterialClass clas : classes.values()) {
			ofy.put(clas);
		}

		super.beforeDelete(dao, ofy, tKeys);
	}
}
