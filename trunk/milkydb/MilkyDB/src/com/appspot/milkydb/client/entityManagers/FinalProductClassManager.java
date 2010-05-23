package com.appspot.milkydb.client.entityManagers;

import com.appspot.milkydb.client.presenter.EditFinalProductClassPresenter;
import com.appspot.milkydb.client.presenter.FinalProductClassPresenter;
import com.appspot.milkydb.client.presenter.Presenter;
import com.appspot.milkydb.client.service.ManagedAsyncService;
import com.appspot.milkydb.client.view.EditFinalProductClassView;
import com.appspot.milkydb.client.view.FinalProductClassView;
import com.appspot.milkydb.shared.dto.SingleKey;
import com.google.gwt.event.shared.HandlerManager;

public class FinalProductClassManager extends AbstractEntityManager {

	private final ManagedAsyncService service;
	private final HandlerManager eventBus;

	public FinalProductClassManager(final ManagedAsyncService service,
			final HandlerManager eventBus) {
		super("finalProductClass");
		this.service = service;
		this.eventBus = eventBus;
	}

	@Override
	protected Presenter getEditPresenter(final SingleKey key) {
		return new EditFinalProductClassPresenter(
				new EditFinalProductClassView(), service, getLocalEventBus(),
				eventBus, key);
	}

	@Override
	protected Presenter getListPresenter() {
		return new FinalProductClassPresenter(new FinalProductClassView(),
				service, getLocalEventBus(), eventBus);
	}

	@Override
	protected Presenter getNewPresenter() {
		return new EditFinalProductClassPresenter(
				new EditFinalProductClassView(), service, getLocalEventBus(),
				eventBus);
	}
}
