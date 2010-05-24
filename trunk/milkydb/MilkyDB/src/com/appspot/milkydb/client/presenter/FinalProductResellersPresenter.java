/**
 * 
 */
package com.appspot.milkydb.client.presenter;

import com.appspot.milkydb.client.service.ManagedAsyncService;
import com.appspot.milkydb.shared.dto.DtoList;
import com.appspot.milkydb.shared.dto.KeyList;
import com.appspot.milkydb.shared.dto.RpcVoid;
import com.appspot.milkydb.shared.models.FinalProductReseller;
import com.appspot.milkydb.shared.service.action.Action;
import com.appspot.milkydb.shared.service.action.ManagerActionSet;
import com.google.gwt.event.shared.HandlerManager;

/**
 * @author burdakovd
 * 
 */
public class FinalProductResellersPresenter extends
		AbstractEntitiesTablePresenter<FinalProductReseller> {

	/**
	 * @param display
	 * @param service
	 * @param localEventBus
	 * @param eventBus
	 */
	public FinalProductResellersPresenter(
			final Display<? super FinalProductReseller> display,
			final ManagedAsyncService service,
			final HandlerManager localEventBus, final HandlerManager eventBus) {
		super(display, service, localEventBus, eventBus);
	}

	@Override
	protected Action<KeyList, RpcVoid> provideDeleteAction() {
		return ManagerActionSet.finalProductReseller.provideDeleteAction();
	}

	@Override
	protected Action<RpcVoid, DtoList<FinalProductReseller>> provideGetAction() {
		return ManagerActionSet.finalProductReseller.provideGetAllAction();
	}

}
