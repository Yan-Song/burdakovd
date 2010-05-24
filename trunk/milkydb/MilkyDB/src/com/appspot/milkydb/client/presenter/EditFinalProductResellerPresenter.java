/**
 * 
 */
package com.appspot.milkydb.client.presenter;

import com.appspot.milkydb.client.service.ManagedAsyncService;
import com.appspot.milkydb.shared.dto.SingleKey;
import com.appspot.milkydb.shared.models.Partner;
import com.appspot.milkydb.shared.service.action.Action;
import com.appspot.milkydb.shared.service.action.ManagerActionSet;
import com.google.gwt.event.shared.HandlerManager;

/**
 * @author burdakovd
 * 
 */
public class EditFinalProductResellerPresenter extends
		AbstractEditPartnerPresenter {

	/**
	 * @param display
	 * @param service
	 * @param localEventBus
	 * @param eventBus
	 */
	public EditFinalProductResellerPresenter(final Display display,
			final ManagedAsyncService service,
			final HandlerManager localEventBus, final HandlerManager eventBus) {
		super(display, service, localEventBus, eventBus);
	}

	/**
	 * @param display
	 * @param service
	 * @param localEventBus
	 * @param eventBus
	 * @param key
	 */
	public EditFinalProductResellerPresenter(final Display display,
			final ManagedAsyncService service,
			final HandlerManager localEventBus, final HandlerManager eventBus,
			final SingleKey key) {
		super(display, service, localEventBus, eventBus, key);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @seecom.appspot.milkydb.client.presenter.AbstractEditEntityPresenter#
	 * provideGetEntityAction()
	 */
	@Override
	protected Action<SingleKey, Partner> provideGetEntityAction() {
		return ManagerActionSet.finalProductReseller.provideGetAction();
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @seecom.appspot.milkydb.client.presenter.AbstractEditEntityPresenter#
	 * provideSaveEntityAction()
	 */
	@Override
	protected Action<Partner, SingleKey> provideSaveEntityAction() {
		return ManagerActionSet.finalProductReseller.provideSaveAction();
	}

}
