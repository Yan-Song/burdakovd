package com.appspot.milkydb.client.entityManagers;

import com.appspot.milkydb.client.presenter.EditRawMaterialProviderPresenter;
import com.appspot.milkydb.client.presenter.Presenter;
import com.appspot.milkydb.client.presenter.RawMaterialProvidersPresenter;
import com.appspot.milkydb.client.service.ManagedAsyncService;
import com.appspot.milkydb.client.view.EditPartnerView;
import com.appspot.milkydb.client.view.RawMaterialProvidersView;
import com.appspot.milkydb.shared.dto.SingleKey;
import com.google.gwt.event.shared.HandlerManager;

public class RawMaterialProviderManager extends AbstractEntityManager {

	private final ManagedAsyncService service;
	private final HandlerManager eventBus;

	/**
	 * @param service
	 * @param eventBus
	 */
	public RawMaterialProviderManager(final ManagedAsyncService service,
			final HandlerManager eventBus) {
		super("rawMaterialProvider");
		this.service = service;
		this.eventBus = eventBus;
	}

	@Override
	protected Presenter getEditPresenter(final SingleKey key) {
		return new EditRawMaterialProviderPresenter(new EditPartnerView(),
				service, getLocalEventBus(), eventBus, key);
	}

	@Override
	protected Presenter getListPresenter() {
		return new RawMaterialProvidersPresenter(
				new RawMaterialProvidersView(), service, getLocalEventBus(),
				eventBus);
	}

	@Override
	protected Presenter getNewPresenter() {
		return new EditRawMaterialProviderPresenter(new EditPartnerView(),
				service, getLocalEventBus(), eventBus);
	}

}
