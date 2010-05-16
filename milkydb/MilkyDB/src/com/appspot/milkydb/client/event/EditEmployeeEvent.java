package com.appspot.milkydb.client.event;

import com.google.gwt.event.shared.GwtEvent;

public class EditEmployeeEvent extends GwtEvent<EditEmployeeEventHandler> {
	public static final Type<EditEmployeeEventHandler> TYPE = new Type<EditEmployeeEventHandler>();

	private final String key;

	public EditEmployeeEvent(final String key) {
		this.key = key;
	}

	@Override
	protected void dispatch(final EditEmployeeEventHandler handler) {
		handler.onEditEmployee(this);
	}

	@Override
	public com.google.gwt.event.shared.GwtEvent.Type<EditEmployeeEventHandler> getAssociatedType() {
		return TYPE;
	}

	public String getKey() {
		return key;
	}
}
