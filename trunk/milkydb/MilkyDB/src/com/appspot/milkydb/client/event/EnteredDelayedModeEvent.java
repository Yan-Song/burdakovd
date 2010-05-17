package com.appspot.milkydb.client.event;

import com.appspot.milkydb.client.service.ManagedAsyncService;
import com.google.gwt.event.shared.GwtEvent;

public class EnteredDelayedModeEvent extends
		GwtEvent<EnteredDelayedModeEventHandler> {
	public static final Type<EnteredDelayedModeEventHandler> TYPE = new Type<EnteredDelayedModeEventHandler>();
	private final ManagedAsyncService service;

	public EnteredDelayedModeEvent(final ManagedAsyncService service) {
		this.service = service;
	}

	@Override
	protected void dispatch(final EnteredDelayedModeEventHandler handler) {
		handler.onEnteredDelayedMode(this);
	}

	@Override
	public com.google.gwt.event.shared.GwtEvent.Type<EnteredDelayedModeEventHandler> getAssociatedType() {
		return TYPE;
	}

	public ManagedAsyncService getservice() {
		return service;
	}
}
