package com.appspot.milkydb.server.services;

import java.util.Collection;
import java.util.List;

import com.appspot.milkydb.server.DAO;
import com.appspot.milkydb.shared.dto.KeyList;
import com.appspot.milkydb.shared.dto.RpcVoid;
import com.appspot.milkydb.shared.models.RawMaterialProvider;
import com.appspot.milkydb.shared.models.Supply;
import com.googlecode.objectify.Key;
import com.googlecode.objectify.Objectify;

public class DeleteRawMaterialProviders extends
		SimpleDeleteEntitiesHandler<RawMaterialProvider> implements
		ActionHandler<KeyList, RpcVoid> {

	public DeleteRawMaterialProviders() {
		super(RawMaterialProvider.class);
	}

	@Override
	protected void checkIfCanDelete(final DAO dao, final Objectify t,
			final Iterable<Key<RawMaterialProvider>> tKeys)
			throws CanNotDeleteException {

		super.checkIfCanDelete(dao, t, tKeys);

		final Collection<RawMaterialProvider> providers = t.get(tKeys).values();

		for (final RawMaterialProvider provider : providers) {
			final List<Key<Supply>> supplies = provider.getSupplies();
			if (!supplies.isEmpty()) {
				throw new CanNotDeleteException(
						"Невозможно удалить поставщика " + provider.getName()
								+ ", есть " + supplies.size()
								+ " заказов от него, нужно сначала удалить их");
			}
		}
	}

}
