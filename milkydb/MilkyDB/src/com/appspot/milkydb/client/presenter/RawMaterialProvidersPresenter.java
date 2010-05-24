package com.appspot.milkydb.client.presenter;

import com.appspot.milkydb.client.service.ManagedAsyncService;
import com.appspot.milkydb.shared.dto.DtoList;
import com.appspot.milkydb.shared.dto.KeyList;
import com.appspot.milkydb.shared.dto.RpcVoid;
import com.appspot.milkydb.shared.models.RawMaterialProvider;
import com.appspot.milkydb.shared.service.action.Action;
import com.appspot.milkydb.shared.service.action.ManagerActionSet;
import com.google.gwt.event.shared.HandlerManager;

public class RawMaterialProvidersPresenter extends
		AbstractEntitiesTablePresenter<RawMaterialProvider> {

	/**
	 * @param display
	 * @param service
	 * @param localEventBus
	 * @param eventBus
	 */
	public RawMaterialProvidersPresenter(
			final Display<? super RawMaterialProvider> display,
			final ManagedAsyncService service,
			final HandlerManager localEventBus, final HandlerManager eventBus) {
		super(display, service, localEventBus, eventBus);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @seecom.appspot.milkydb.client.presenter.AbstractEntitiesTablePresenter#
	 * provideDeleteAction()
	 */
	@Override
	protected Action<KeyList, RpcVoid> provideDeleteAction() {
		return ManagerActionSet.rawMaterialProvider.provideDeleteAction();
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @seecom.appspot.milkydb.client.presenter.AbstractEntitiesTablePresenter#
	 * provideGetAction()
	 */
	@Override
	protected Action<RpcVoid, DtoList<RawMaterialProvider>> provideGetAction() {
		return ManagerActionSet.rawMaterialProvider.provideGetAllAction();
	}

}
