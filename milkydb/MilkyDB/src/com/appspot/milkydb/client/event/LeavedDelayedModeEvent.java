package com.appspot.milkydb.client.event;

import com.appspot.milkydb.client.service.ManagedAsyncService;
import com.google.gwt.event.shared.GwtEvent;

public class LeavedDelayedModeEvent extends
		GwtEvent<LeavedDelayedModeEventHandler> {
	public static final Type<LeavedDelayedModeEventHandler> TYPE = new Type<LeavedDelayedModeEventHandler>();
	private final ManagedAsyncService service;

	public LeavedDelayedModeEvent(final ManagedAsyncService service) {
		this.service = service;
	}

	@Override
	protected void dispatch(final LeavedDelayedModeEventHandler handler) {
		handler.onLeavedDelayedMode(this);
	}

	@Override
	public com.google.gwt.event.shared.GwtEvent.Type<LeavedDelayedModeEventHandler> getAssociatedType() {
		return TYPE;
	}

	public ManagedAsyncService getservice() {
		return service;
	}
}
