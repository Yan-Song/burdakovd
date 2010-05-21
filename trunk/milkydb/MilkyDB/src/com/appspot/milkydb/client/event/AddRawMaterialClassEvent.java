package com.appspot.milkydb.client.event;

import com.google.gwt.event.shared.GwtEvent;

public class AddRawMaterialClassEvent extends
		GwtEvent<AddRawMaterialClassEventHandler> {
	public static final Type<AddRawMaterialClassEventHandler> TYPE = new Type<AddRawMaterialClassEventHandler>();

	@Override
	protected void dispatch(final AddRawMaterialClassEventHandler handler) {
		handler.onAddRawMaterialClass(this);
	}

	@Override
	public com.google.gwt.event.shared.GwtEvent.Type<AddRawMaterialClassEventHandler> getAssociatedType() {
		return TYPE;
	}
}
