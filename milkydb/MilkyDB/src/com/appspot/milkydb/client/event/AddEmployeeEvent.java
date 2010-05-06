package com.appspot.milkydb.client.event;

import com.google.gwt.event.shared.GwtEvent;

public class AddEmployeeEvent extends GwtEvent<AddEmployeeEventHandler> {
	public static final Type<AddEmployeeEventHandler> TYPE = new Type<AddEmployeeEventHandler>();

	@Override
	protected void dispatch(final AddEmployeeEventHandler handler) {
		handler.onAddEmployee(this);
	}

	@Override
	public com.google.gwt.event.shared.GwtEvent.Type<AddEmployeeEventHandler> getAssociatedType() {
		return TYPE;
	}
}
