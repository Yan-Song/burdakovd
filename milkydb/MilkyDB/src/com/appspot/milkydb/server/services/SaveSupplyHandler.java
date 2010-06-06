/**
 * 
 */
package com.appspot.milkydb.server.services;

import com.appspot.milkydb.client.validation.ValidationError;
import com.appspot.milkydb.server.DAO;
import com.appspot.milkydb.shared.dto.SingleKey;
import com.appspot.milkydb.shared.models.RawMaterialClass;
import com.appspot.milkydb.shared.models.RawMaterialProvider;
import com.appspot.milkydb.shared.models.Supply;
import com.googlecode.objectify.Key;
import com.googlecode.objectify.Objectify;

/**
 * @author burdakovd
 * 
 */
public class SaveSupplyHandler extends
		AbstractSaveEntityHandler<Supply, Supply> implements
		ActionHandler<Supply, SingleKey> {

	/**
	 * @param modelClass
	 */
	public SaveSupplyHandler() {
		super(Supply.class);
	}

	@Override
	protected void afterSave(final Objectify ofy, final Supply oldModel,
			final Supply newModel) {
		final Key<Supply> key = new Key<Supply>(DAO.rootKey, Supply.class,
				newModel.getKey());

		if (!newModel.getProvider().equals(oldModel.getProvider())) {

			final RawMaterialProvider provider = ofy
					.get(newModel.getProvider());

			provider.getSupplies().add(key);

			ofy.put(provider);
		}

		if (!newModel.getMaterialClass().equals(oldModel.getMaterialClass())) {
			final RawMaterialClass clas = ofy.get(newModel.getMaterialClass());

			clas.getContracts().add(key);

			ofy.put(clas);
		}
	}

	@Override
	protected void setData(final Objectify ofy, final Supply model,
			final Supply dto) throws ValidationError {

		if (model.getKey() != null) {
			final Key<Supply> key = new Key<Supply>(DAO.rootKey, Supply.class,
					model.getKey());

			if (!model.getProvider().equals(dto.getProvider())) {

				final RawMaterialProvider provider = ofy.get(model
						.getProvider());

				provider.getSupplies().remove(key);

				ofy.put(provider);
			}

			if (!model.getMaterialClass().equals(dto.getMaterialClass())) {
				final RawMaterialClass clas = ofy.get(model.getMaterialClass());

				clas.getContracts().remove(key);

				ofy.put(clas);
			}
		}
	}
}
