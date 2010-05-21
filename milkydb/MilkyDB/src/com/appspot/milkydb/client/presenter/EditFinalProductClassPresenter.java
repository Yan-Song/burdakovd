package com.appspot.milkydb.client.presenter;

import com.appspot.milkydb.client.service.ManagedAsyncService;
import com.appspot.milkydb.shared.dto.EncodedKey;
import com.appspot.milkydb.shared.dto.FullProductClass;
import com.appspot.milkydb.shared.service.action.Action;
import com.appspot.milkydb.shared.service.action.ManagerActionSet;
import com.google.gwt.event.shared.HandlerManager;

public class EditFinalProductClassPresenter extends
		AbstractEditProductClassPresenter {

	public interface Display extends AbstractEditProductClassPresenter.Display {
	}

	public EditFinalProductClassPresenter(final Display display,
			final ManagedAsyncService service,
			final HandlerManager localEventBus, final HandlerManager eventBus) {
		this(display, service, localEventBus, eventBus, null);

	}

	public EditFinalProductClassPresenter(final Display display,
			final ManagedAsyncService service,
			final HandlerManager localEventBus, final HandlerManager eventBus,
			final EncodedKey key) {
		super(display, service, localEventBus, eventBus, key);
	}

	@Override
	protected Action<EncodedKey, FullProductClass> provideGetEntityAction() {
		return ManagerActionSet.FinalProductClass.provideGetAction();
	}

	@Override
	protected Action<FullProductClass, EncodedKey> provideSaveEntityAction() {
		return ManagerActionSet.FinalProductClass.provideSaveAction();
	}

}
