package com.appspot.milkydb.client.event;

import com.appspot.milkydb.client.service.AsyncRequest;
import com.google.gwt.event.shared.GwtEvent;

public class RpcFailureEvent extends GwtEvent<RpcFailureEventHandler> {
	public static final Type<RpcFailureEventHandler> TYPE = new Type<RpcFailureEventHandler>();
	private final AsyncRequest<?, ?> request;
	private final Throwable failure;

	public RpcFailureEvent(final AsyncRequest<?, ?> request,
			final Throwable failure) {
		this.request = request;
		this.failure = failure;
	}

	@Override
	protected void dispatch(final RpcFailureEventHandler handler) {
		handler.onRpcFailure(this);
	}

	@Override
	public com.google.gwt.event.shared.GwtEvent.Type<RpcFailureEventHandler> getAssociatedType() {
		return TYPE;
	}

	public Throwable getFailure() {
		return failure;
	}

	public AsyncRequest<?, ?> getRequest() {
		return request;
	}
}
