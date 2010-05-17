package com.appspot.milkydb.client.event;

import com.appspot.milkydb.client.service.AsyncRequest;
import com.google.gwt.event.shared.GwtEvent;

public class RpcSuccessEvent extends GwtEvent<RpcSuccessEventHandler> {
	public static final Type<RpcSuccessEventHandler> TYPE = new Type<RpcSuccessEventHandler>();
	private final AsyncRequest<?, ?> request;

	public RpcSuccessEvent(final AsyncRequest<?, ?> request) {
		this.request = request;
	}

	@Override
	protected void dispatch(final RpcSuccessEventHandler handler) {
		handler.onRpcSuccess(this);
	}

	@Override
	public com.google.gwt.event.shared.GwtEvent.Type<RpcSuccessEventHandler> getAssociatedType() {
		return TYPE;
	}

	public AsyncRequest<?, ?> getRequest() {
		return request;
	}
}
