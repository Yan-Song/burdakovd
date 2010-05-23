package com.appspot.milkydb.client.entityManagers;

import com.appspot.milkydb.client.presenter.EditEmployeePresenter;
import com.appspot.milkydb.client.presenter.EmployeePresenter;
import com.appspot.milkydb.client.presenter.Presenter;
import com.appspot.milkydb.client.service.ManagedAsyncService;
import com.appspot.milkydb.client.view.EditEmployeeView;
import com.appspot.milkydb.client.view.EmployeeView;
import com.appspot.milkydb.shared.dto.SingleKey;
import com.google.gwt.event.shared.HandlerManager;

public class EmployeeManager extends AbstractEntityManager {

	private final ManagedAsyncService service;
	private final HandlerManager eventBus;

	public EmployeeManager(final ManagedAsyncService service,
			final HandlerManager eventBus) {
		super("employee");
		this.service = service;
		this.eventBus = eventBus;
	}

	@Override
	protected Presenter getEditPresenter(final SingleKey key) {
		return new EditEmployeePresenter(new EditEmployeeView(), service,
				getLocalEventBus(), eventBus, key);
	}

	@Override
	protected Presenter getListPresenter() {
		return new EmployeePresenter(new EmployeeView(), service,
				getLocalEventBus(), eventBus);
	}

	@Override
	protected Presenter getNewPresenter() {
		return new EditEmployeePresenter(new EditEmployeeView(), service,
				getLocalEventBus(), eventBus);
	}
}
