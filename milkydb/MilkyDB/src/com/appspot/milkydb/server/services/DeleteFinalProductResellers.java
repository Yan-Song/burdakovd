/**
 * 
 */
package com.appspot.milkydb.server.services;

import java.util.Collection;
import java.util.List;

import com.appspot.milkydb.server.DAO;
import com.appspot.milkydb.shared.dto.KeyList;
import com.appspot.milkydb.shared.dto.RpcVoid;
import com.appspot.milkydb.shared.models.Demand;
import com.appspot.milkydb.shared.models.FinalProductReseller;
import com.googlecode.objectify.Key;
import com.googlecode.objectify.Objectify;

/**
 * @author burdakovd
 * 
 */
public class DeleteFinalProductResellers extends
		SimpleDeleteEntitiesHandler<FinalProductReseller> implements
		ActionHandler<KeyList, RpcVoid> {

	public DeleteFinalProductResellers() {
		super(FinalProductReseller.class);
	}

	@Override
	protected void checkIfCanDelete(final DAO dao, final Objectify t,
			final Iterable<Key<FinalProductReseller>> tKeys)
			throws CanNotDeleteException {

		super.checkIfCanDelete(dao, t, tKeys);

		final Collection<FinalProductReseller> resellers = t.get(tKeys)
				.values();

		for (final FinalProductReseller reseller : resellers) {
			final List<Key<Demand>> demands = reseller.getDemands();
			if (!demands.isEmpty()) {
				throw new CanNotDeleteException("Невозможно удалить магазин "
						+ reseller.getName() + ", есть " + demands.size()
						+ " заказов от него, нужно сначала удалить их");
			}
		}
	}

}
