package com.appspot.milkydb.client.presenter;

import com.appspot.milkydb.client.service.ManagedAsyncService;
import com.appspot.milkydb.shared.dto.DtoList;
import com.appspot.milkydb.shared.dto.EncodedKeys;
import com.appspot.milkydb.shared.dto.LightEmployee;
import com.appspot.milkydb.shared.dto.RpcVoid;
import com.appspot.milkydb.shared.service.action.Action;
import com.appspot.milkydb.shared.service.action.ManagerActionSet;
import com.google.gwt.event.shared.HandlerManager;

public class EmployeePresenter extends
		AbstractEntitiesTablePresenter<LightEmployee> {

	public interface Display extends
			AbstractEntitiesTablePresenter.Display<LightEmployee> {
	}

	public EmployeePresenter(final Display display,
			final ManagedAsyncService service,
			final HandlerManager localEventBus, final HandlerManager eventBus) {
		super(display, service, localEventBus, eventBus);
	}

	@Override
	protected Action<EncodedKeys, RpcVoid> provideDeleteAction() {
		return ManagerActionSet.Employee.provideDeleteAction();
	}

	@Override
	protected Action<RpcVoid, DtoList<LightEmployee>> provideGetAction() {
		return ManagerActionSet.Employee.provideGetAllAction();
	}
}
