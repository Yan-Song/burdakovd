package com.appspot.milkydb.client.service;

import java.util.HashSet;
import java.util.Set;

import com.appspot.milkydb.client.event.DelayedModeTickEvent;
import com.appspot.milkydb.client.event.EnteredDelayedModeEvent;
import com.appspot.milkydb.client.event.LeavedDelayedModeEvent;
import com.appspot.milkydb.client.event.RpcFailureEvent;
import com.appspot.milkydb.client.event.RpcSuccessEvent;
import com.appspot.milkydb.shared.dto.RpcRequest;
import com.appspot.milkydb.shared.dto.RpcResponse;
import com.appspot.milkydb.shared.service.MilkyServiceAsync;
import com.appspot.milkydb.shared.service.action.Action;
import com.google.gwt.event.shared.HandlerManager;
import com.google.gwt.user.client.Timer;
import com.google.gwt.user.client.rpc.AsyncCallback;
import com.google.gwt.user.client.rpc.InvocationException;

public class ManagedAsyncService {
	private final Set<AsyncRequest<?, ?>> requests = new HashSet<AsyncRequest<?, ?>>();
	private final HandlerManager eventBus;
	private final MilkyServiceAsync realService;

	private final int startDelay = 1000;
	private final int maxDelay = 30000;
	private int delay = startDelay;
	private boolean delayed = false;

	private int secondsBeforeRetry;

	private final Timer timer = new Timer() {
		@Override
		public void run() {
			delay = Math.min(delay * 2, maxDelay);
			this.schedule(delay);
			executeAllIfNeeded();
		}

		@Override
		public void schedule(final int ms) {
			super.schedule(ms);
			secondsBeforeRetry = ms / 1000;
		}
	};

	private final Timer tick = new Timer() {
		@Override
		public void run() {
			secondsBeforeRetry -= 1;
			eventBus.fireEvent(new DelayedModeTickEvent(
					ManagedAsyncService.this));
		}
	};

	public ManagedAsyncService(final MilkyServiceAsync realService,
			final HandlerManager eventBus) {
		this.realService = realService;
		this.eventBus = eventBus;

	};

	private void enterDelayedMode() {
		delayed = true;
		delay = startDelay;
		timer.schedule(delay);
		tick.scheduleRepeating(1000);
		eventBus.fireEvent(new EnteredDelayedModeEvent(this));
	}

	public <Req extends RpcRequest, Resp extends RpcResponse> AsyncRequest<Req, Resp> execute(
			final Action<Req, Resp> action, final Req request,
			final AsyncCallback<Resp> callback) {
		return execute(action, request, callback, action.getName());
	}

	public <Req extends RpcRequest, Resp extends RpcResponse> AsyncRequest<Req, Resp> execute(
			final Action<Req, Resp> action, final Req request,
			final AsyncCallback<Resp> callback, final String name) {

		final AsyncRequest<Req, Resp> a = new AsyncRequest<Req, Resp>(
				realService, this, action, request, callback, name);
		requests.add(a);
		if (!delayed) {
			executeAllIfNeeded();
		}
		return a;
	}

	private void executeAll() {
		for (final AsyncRequest<?, ?> request : requests) {
			assert !request.isCompleted() : "найден completed request в очереди: "
					+ request.getName();
			if (!request.isExecuting()) {
				request.execute();
			}
		}
	}

	private void executeAllIfNeeded() {
		executeAll();
	}

	public int getSecondsBeforeNextRetry() {
		return delayed ? Math.max(secondsBeforeRetry, 0) : 0;
	}

	public boolean isInDelayedMode() {
		return delayed;
	}

	private void leaveDelayedMode() {
		delayed = false;
		timer.cancel();
		tick.cancel();
		executeAllIfNeeded();
		eventBus.fireEvent(new LeavedDelayedModeEvent(this));
	}

	private void onFailedInvocation() {
		if (!delayed) {
			enterDelayedMode();
		}
	}

	void onFailure(final AsyncRequest<?, ?> request, final Throwable failure) {
		if (failure instanceof InvocationException) {
			onFailedInvocation();
		} else {
			request.complete();
			requests.remove(request);
			onSuccessfulInvocation();
			eventBus.fireEvent(new RpcFailureEvent(request, failure));
			request.getCallback().onFailure(failure);
		}
	}

	<Response extends RpcResponse> void onSuccess(
			final AsyncRequest<?, Response> request, final Response result) {
		request.complete();
		requests.remove(request);
		onSuccessfulInvocation();
		eventBus.fireEvent(new RpcSuccessEvent(request));
		request.getCallback().onSuccess(result);
	}

	private void onSuccessfulInvocation() {
		if (delayed) {
			leaveDelayedMode();
		}
	}

	public void retryNow() {
		if (delayed) {
			leaveDelayedMode();
		}
	}
}
