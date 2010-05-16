package com.appspot.milkydb.client.event;

import com.google.gwt.event.shared.GwtEvent;

public class EditEmployeeFinishedEvent extends
		GwtEvent<EditEmployeeFinishedEventHandler> {
	public static final Type<EditEmployeeFinishedEventHandler> TYPE = new Type<EditEmployeeFinishedEventHandler>();

	@Override
	protected void dispatch(final EditEmployeeFinishedEventHandler handler) {
		handler.onEditEmployeeFinished(this);
	}

	@Override
	public com.google.gwt.event.shared.GwtEvent.Type<EditEmployeeFinishedEventHandler> getAssociatedType() {
		return TYPE;
	}
}
