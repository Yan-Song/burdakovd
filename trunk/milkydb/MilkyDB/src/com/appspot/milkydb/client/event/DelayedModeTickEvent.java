package com.appspot.milkydb.client.event;

import com.appspot.milkydb.client.service.ManagedAsyncService;
import com.google.gwt.event.shared.GwtEvent;

public class DelayedModeTickEvent extends GwtEvent<DelayedModeTickEventHandler> {
	public static final Type<DelayedModeTickEventHandler> TYPE = new Type<DelayedModeTickEventHandler>();
	private final ManagedAsyncService service;

	public DelayedModeTickEvent(final ManagedAsyncService service) {
		this.service = service;
	}

	@Override
	protected void dispatch(final DelayedModeTickEventHandler handler) {
		handler.onDelayedModeTick(this);
	}

	@Override
	public com.google.gwt.event.shared.GwtEvent.Type<DelayedModeTickEventHandler> getAssociatedType() {
		return TYPE;
	}

	public ManagedAsyncService getservice() {
		return service;
	}
}
