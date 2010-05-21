package com.appspot.milkydb.client.presenter;

import com.appspot.milkydb.client.event.AddEmployeeEvent;
import com.appspot.milkydb.client.event.EditEmployeeEvent;
import com.appspot.milkydb.client.service.ManagedAsyncService;
import com.appspot.milkydb.shared.dto.DtoList;
import com.appspot.milkydb.shared.dto.EncodedKeys;
import com.appspot.milkydb.shared.dto.LightEmployee;
import com.appspot.milkydb.shared.dto.RpcVoid;
import com.appspot.milkydb.shared.service.Action;
import com.google.gwt.event.shared.HandlerManager;

public class EmployeePresenter extends
		AbstractEntitiesTablePresenter<LightEmployee> {

	public interface Display extends
			AbstractEntitiesTablePresenter.Display<LightEmployee> {
	}

	public EmployeePresenter(final Display display,
			final ManagedAsyncService service, final HandlerManager eventBus) {
		super(display, service, eventBus);
	}

	@Override
	protected void fireAddEntityEvent() {
		eventBus.fireEvent(new AddEmployeeEvent());
	}

	@Override
	protected void fireEditEntityEvent(final String key) {
		eventBus.fireEvent(new EditEmployeeEvent(key));
	}

	@Override
	protected Action<EncodedKeys, RpcVoid> provideDeleteAction() {
		return Action.deleteEmployee;
	}

	@Override
	protected Action<RpcVoid, DtoList<LightEmployee>> provideGetAction() {
		return Action.getLightEmployeeList;
	}
}
