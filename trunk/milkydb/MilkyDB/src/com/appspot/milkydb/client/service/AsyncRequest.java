package com.appspot.milkydb.client.service;

import java.io.Serializable;

import com.appspot.milkydb.shared.service.Action;
import com.appspot.milkydb.shared.service.MilkyServiceAsync;
import com.google.gwt.user.client.rpc.AsyncCallback;

public class AsyncRequest<Req extends Serializable, Resp extends Serializable> {

	private final MilkyServiceAsync realService;
	private final ManagedAsyncService managed;
	private final Action<Req, Resp> action;
	private final Req request;
	private final AsyncCallback<Resp> callback;
	private final String name;
	private boolean completed = false;
	private boolean executing = false;

	AsyncRequest(final MilkyServiceAsync service,
			final ManagedAsyncService managed, final Action<Req, Resp> action,
			final Req request, final AsyncCallback<Resp> callback,
			final String name) {
		this.realService = service;
		this.managed = managed;
		this.action = action;
		this.request = request;
		this.callback = callback;
		this.name = name;

	}

	void complete() {
		completed = true;
	}

	void execute() {
		assert !executing;
		assert !completed;
		executing = true;

		realService.execute(action, request, new AsyncCallback<Resp>() {

			@Override
			public void onFailure(final Throwable caught) {
				executing = false;
				managed.onFailure(AsyncRequest.this, caught);
			}

			@Override
			public void onSuccess(final Resp result) {
				executing = false;
				managed.onSuccess(AsyncRequest.this, result);
			}
		});
	}

	AsyncCallback<Resp> getCallback() {
		return callback;
	}

	public String getName() {
		return name;
	}

	public boolean isCompleted() {
		return completed;
	}

	public boolean isExecuting() {
		return executing;
	}
}
