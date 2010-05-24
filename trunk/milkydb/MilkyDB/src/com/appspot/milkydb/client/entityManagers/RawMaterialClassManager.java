package com.appspot.milkydb.client.entityManagers;

import com.appspot.milkydb.client.presenter.EditRawMaterialClassPresenter;
import com.appspot.milkydb.client.presenter.Presenter;
import com.appspot.milkydb.client.presenter.RawMaterialClassesPresenter;
import com.appspot.milkydb.client.service.ManagedAsyncService;
import com.appspot.milkydb.client.view.EditRawMaterialClassView;
import com.appspot.milkydb.client.view.RawMaterialClassesView;
import com.appspot.milkydb.shared.dto.SingleKey;
import com.google.gwt.event.shared.HandlerManager;

public class RawMaterialClassManager extends AbstractEntityManager {

	private final ManagedAsyncService service;
	private final HandlerManager eventBus;

	public RawMaterialClassManager(final ManagedAsyncService service,
			final HandlerManager eventBus) {
		super("rawMaterialClass");
		this.service = service;
		this.eventBus = eventBus;
	}

	@Override
	protected Presenter getEditPresenter(final SingleKey key) {
		return new EditRawMaterialClassPresenter(
				new EditRawMaterialClassView(), service, getLocalEventBus(),
				eventBus, key);
	}

	@Override
	protected Presenter getListPresenter() {
		return new RawMaterialClassesPresenter(new RawMaterialClassesView(),
				service, getLocalEventBus(), eventBus);
	}

	@Override
	protected Presenter getNewPresenter() {
		return new EditRawMaterialClassPresenter(
				new EditRawMaterialClassView(), service, getLocalEventBus(),
				eventBus);
	}
}
