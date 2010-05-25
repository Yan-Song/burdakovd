package com.appspot.milkydb.client.presenter;

import com.appspot.milkydb.client.service.ManagedAsyncService;
import com.appspot.milkydb.shared.dto.DtoList;
import com.appspot.milkydb.shared.dto.KeyList;
import com.appspot.milkydb.shared.dto.RpcVoid;
import com.appspot.milkydb.shared.models.FinalProductClass;
import com.appspot.milkydb.shared.service.action.Action;
import com.appspot.milkydb.shared.service.action.ManagerActionSet;
import com.google.gwt.event.shared.HandlerManager;

public class FinalProductClassesPresenter extends
		AbstractEntitiesTablePresenter<FinalProductClass> {

	public FinalProductClassesPresenter(
			final Display<FinalProductClass> display,
			final ManagedAsyncService service,
			final HandlerManager localEventBus, final HandlerManager eventBus) {
		super(display, service, localEventBus, eventBus);
	}

	@Override
	protected Action<KeyList, RpcVoid> provideDeleteAction() {
		return ManagerActionSet.finalProductClass.provideDeleteAction();
	}

	@Override
	protected Action<RpcVoid, DtoList<FinalProductClass>> provideGetAction() {
		return ManagerActionSet.finalProductClass.provideGetAllAction();
	}

}
