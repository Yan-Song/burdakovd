package com.appspot.milkydb.client.presenter;

import com.appspot.milkydb.client.service.ManagedAsyncService;
import com.appspot.milkydb.shared.dto.SingleKey;
import com.appspot.milkydb.shared.models.Partner;
import com.appspot.milkydb.shared.service.action.Action;
import com.appspot.milkydb.shared.service.action.ManagerActionSet;
import com.google.gwt.event.shared.HandlerManager;

public class EditRawMaterialProviderPresenter extends AbstractEditPartnerPresenter {

	public EditRawMaterialProviderPresenter(final Display display,
			final ManagedAsyncService service,
			final HandlerManager localEventBus, final HandlerManager eventBus) {
		super(display, service, localEventBus, eventBus);
	}

	public EditRawMaterialProviderPresenter(final Display display,
			final ManagedAsyncService service,
			final HandlerManager localEventBus, final HandlerManager eventBus,
			final SingleKey key) {
		super(display, service, localEventBus, eventBus, key);
	}

	@Override
	protected Action<SingleKey, Partner> provideGetEntityAction() {
		return ManagerActionSet.rawMaterialProvider.provideGetAction();
	}

	@Override
	protected Action<Partner, SingleKey> provideSaveEntityAction() {
		return ManagerActionSet.rawMaterialProvider.provideSaveAction();
	}

}
