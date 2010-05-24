/**
 * 
 */
package com.appspot.milkydb.client.entityManagers;

import com.appspot.milkydb.client.presenter.EditFinalProductResellerPresenter;
import com.appspot.milkydb.client.presenter.FinalProductResellersPresenter;
import com.appspot.milkydb.client.presenter.Presenter;
import com.appspot.milkydb.client.service.ManagedAsyncService;
import com.appspot.milkydb.client.view.EditPartnerView;
import com.appspot.milkydb.client.view.FinalProductResellersView;
import com.appspot.milkydb.shared.dto.SingleKey;
import com.google.gwt.event.shared.HandlerManager;

/**
 * @author burdakovd
 * 
 */
public class FinalProductResellerManager extends AbstractEntityManager {

	private final ManagedAsyncService service;
	private final HandlerManager eventBus;

	public FinalProductResellerManager(final ManagedAsyncService service,
			final HandlerManager eventBus) {
		super("finalProductReseller");
		this.service = service;
		this.eventBus = eventBus;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @seecom.appspot.milkydb.client.entityManagers.AbstractEntityManager#
	 * getEditPresenter(com.appspot.milkydb.shared.dto.SingleKey)
	 */
	@Override
	protected Presenter getEditPresenter(final SingleKey key) {
		return new EditFinalProductResellerPresenter(new EditPartnerView(),
				service, getLocalEventBus(), eventBus, key);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @seecom.appspot.milkydb.client.entityManagers.AbstractEntityManager#
	 * getListPresenter()
	 */
	@Override
	protected Presenter getListPresenter() {
		return new FinalProductResellersPresenter(
				new FinalProductResellersView(), service, getLocalEventBus(),
				eventBus);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @seecom.appspot.milkydb.client.entityManagers.AbstractEntityManager#
	 * getNewPresenter()
	 */
	@Override
	protected Presenter getNewPresenter() {
		return new EditFinalProductResellerPresenter(new EditPartnerView(),
				service, getLocalEventBus(), eventBus);
	}

}
