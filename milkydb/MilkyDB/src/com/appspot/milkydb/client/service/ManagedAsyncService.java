package com.appspot.milkydb.client.service;

import java.io.Serializable;
import java.util.HashSet;
import java.util.Set;

import com.appspot.milkydb.client.event.RpcFailureEvent;
import com.appspot.milkydb.client.event.RpcSuccessEvent;
import com.appspot.milkydb.shared.services.Action;
import com.appspot.milkydb.shared.services.MilkyServiceAsync;
import com.google.gwt.event.shared.HandlerManager;
import com.google.gwt.user.client.rpc.AsyncCallback;

public class ManagedAsyncService {
	private final Set<AsyncRequest<?, ?>> requests = new HashSet<AsyncRequest<?, ?>>();
	private final HandlerManager eventBus;
	private final MilkyServiceAsync realService;

	public ManagedAsyncService(final MilkyServiceAsync realService,
			final HandlerManager eventBus) {
		this.realService = realService;
		this.eventBus = eventBus;

	}

	public <Req extends Serializable, Resp extends Serializable> AsyncRequest<Req, Resp> execute(
			final Action<Req, Resp> action, final Req request,
			final AsyncCallback<Resp> callback) {
		return execute(action, request, callback, action.getName());
	}

	public <Req extends Serializable, Resp extends Serializable> AsyncRequest<Req, Resp> execute(
			final Action<Req, Resp> action, final Req request,
			final AsyncCallback<Resp> callback, final String name) {

		final AsyncRequest<Req, Resp> a = new AsyncRequest<Req, Resp>(
				realService, this, action, request, callback, name);
		requests.add(a);
		executeAllIfNeeded();
		return a;
	}

	private void executeAll() {
		for (final AsyncRequest<?, ?> request : requests) {
			if (!request.isExecuting()) {
				request.execute();
			}
		}
	}

	private void executeAllIfNeeded() {
		executeAll();
	}

	void onFailure(final AsyncRequest<?, ?> request, final Throwable failure) {
		request.complete();
		requests.remove(request);
		eventBus.fireEvent(new RpcFailureEvent(request, failure));
		// todo: тут можно перехватывать сетевые ошибки и "retry"
		// и тогда оставлять request для повтора
	}

	void onSuccess(final AsyncRequest<?, ?> request) {
		requests.remove(request);
		eventBus.fireEvent(new RpcSuccessEvent(request));
	}
}
