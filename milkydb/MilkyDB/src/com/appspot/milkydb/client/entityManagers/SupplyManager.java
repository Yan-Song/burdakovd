/**
 * 
 */
package com.appspot.milkydb.client.entityManagers;

import com.appspot.milkydb.client.presenter.Presenter;
import com.appspot.milkydb.client.service.ManagedAsyncService;
import com.appspot.milkydb.shared.dto.SingleKey;
import com.google.gwt.event.shared.HandlerManager;

/**
 * @author burdakovd
 * 
 */
public class SupplyManager extends AbstractEntityManager {

	private final HandlerManager eventBus;
	private final ManagedAsyncService service;

	/**
	 * @param baseUrl
	 */
	public SupplyManager(final ManagedAsyncService service,
			final HandlerManager eventBus) {
		super("supply");
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
		// TODO Auto-generated method stub
		return null;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @seecom.appspot.milkydb.client.entityManagers.AbstractEntityManager#
	 * getListPresenter()
	 */
	@Override
	protected Presenter getListPresenter() {
		// TODO Auto-generated method stub
		return null;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @seecom.appspot.milkydb.client.entityManagers.AbstractEntityManager#
	 * getNewPresenter()
	 */
	@Override
	protected Presenter getNewPresenter() {
		// TODO Auto-generated method stub
		return null;
	}

}
