package com.appspot.milkydb.client.presenter;

import java.util.ArrayList;

import com.appspot.milkydb.client.event.AddEmployeeEvent;
import com.appspot.milkydb.client.event.EditEmployeeEvent;
import com.appspot.milkydb.client.service.ManagedAsyncService;
import com.appspot.milkydb.shared.dto.LightEmployee;
import com.appspot.milkydb.shared.dto.SerializableVoid;
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
	protected Action<ArrayList<String>, SerializableVoid> provideDeleteAction() {
		return Action.deleteEmployee;
	}

	@Override
	protected Action<SerializableVoid, ArrayList<LightEmployee>> provideGetAction() {
		return Action.getLightEmployeeList;
	}
}
