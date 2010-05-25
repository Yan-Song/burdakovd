package com.appspot.milkydb.client.presenter;

import com.appspot.milkydb.client.service.ManagedAsyncService;
import com.appspot.milkydb.shared.dto.DtoList;
import com.appspot.milkydb.shared.dto.KeyList;
import com.appspot.milkydb.shared.dto.RpcVoid;
import com.appspot.milkydb.shared.models.RawMaterialClass;
import com.appspot.milkydb.shared.service.action.Action;
import com.appspot.milkydb.shared.service.action.ManagerActionSet;
import com.google.gwt.event.shared.HandlerManager;

public class RawMaterialClassesPresenter extends
		AbstractEntitiesTablePresenter<RawMaterialClass> {

	public interface Display extends
			AbstractEntitiesTablePresenter.Display<RawMaterialClass> {
	}

	public RawMaterialClassesPresenter(final Display display,
			final ManagedAsyncService service,
			final HandlerManager localEventBus, final HandlerManager eventBus) {
		super(display, service, localEventBus, eventBus);
	}

	@Override
	protected Action<KeyList, RpcVoid> provideDeleteAction() {
		return ManagerActionSet.rawMaterialClass.provideDeleteAction();
	}

	@Override
	protected Action<RpcVoid, DtoList<RawMaterialClass>> provideGetAction() {
		return ManagerActionSet.rawMaterialClass.provideGetAllAction();
	}
}
