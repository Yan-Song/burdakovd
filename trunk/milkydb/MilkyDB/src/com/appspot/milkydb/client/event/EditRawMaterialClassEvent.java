package com.appspot.milkydb.client.event;

import com.google.gwt.event.shared.GwtEvent;

public class EditRawMaterialClassEvent extends
		GwtEvent<EditRawMaterialClassEventHandler> {
	public static final Type<EditRawMaterialClassEventHandler> TYPE = new Type<EditRawMaterialClassEventHandler>();

	private final String key;

	public EditRawMaterialClassEvent(final String key) {
		this.key = key;
	}

	@Override
	protected void dispatch(final EditRawMaterialClassEventHandler handler) {
		handler.onEditRawMaterialClass(this);
	}

	@Override
	public com.google.gwt.event.shared.GwtEvent.Type<EditRawMaterialClassEventHandler> getAssociatedType() {
		return TYPE;
	}

	public String getKey() {
		return key;
	}
}
