package com.appspot.milkydb.client.presenter;

import com.appspot.milkydb.client.service.ManagedAsyncService;
import com.appspot.milkydb.shared.dto.SingleKey;
import com.appspot.milkydb.shared.models.BaseProductClass;
import com.appspot.milkydb.shared.service.action.Action;
import com.appspot.milkydb.shared.service.action.ManagerActionSet;
import com.google.gwt.event.shared.HandlerManager;

public class EditRawMaterialClassPresenter extends
		AbstractEditProductClassPresenter {

	public interface Display extends AbstractEditProductClassPresenter.Display {
	}

	public EditRawMaterialClassPresenter(final Display display,
			final ManagedAsyncService service,
			final HandlerManager localEventBus, final HandlerManager eventBus) {
		super(display, service, localEventBus, eventBus);
	}

	public EditRawMaterialClassPresenter(final Display display,
			final ManagedAsyncService service,
			final HandlerManager localEventBus, final HandlerManager eventBus,
			final SingleKey key) {
		super(display, service, localEventBus, eventBus, key);
	}

	@Override
	protected Action<SingleKey, BaseProductClass> provideGetEntityAction() {
		return ManagerActionSet.RawMaterialClass.provideGetAction();
	}

	@Override
	protected Action<BaseProductClass, SingleKey> provideSaveEntityAction() {
		return ManagerActionSet.RawMaterialClass.provideSaveAction();
	}

}
