package com.appspot.milkydb.client.event;

import com.google.gwt.event.shared.GwtEvent;

public class EditEmployeeCancelledEvent extends
		GwtEvent<EditEmployeeCancelledEventHandler> {
	public static final Type<EditEmployeeCancelledEventHandler> TYPE = new Type<EditEmployeeCancelledEventHandler>();

	@Override
	protected void dispatch(final EditEmployeeCancelledEventHandler handler) {
		handler.onEditEventCancelled(this);
	}

	@Override
	public com.google.gwt.event.shared.GwtEvent.Type<EditEmployeeCancelledEventHandler> getAssociatedType() {
		return TYPE;
	}
}
