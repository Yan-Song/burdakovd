package com.appspot.milkydb.client.ui;

import java.util.ArrayList;
import java.util.List;

import com.appspot.milkydb.client.event.RpcFailureEvent;
import com.appspot.milkydb.client.event.RpcFailureEventHandler;
import com.appspot.milkydb.client.event.RpcSuccessEvent;
import com.appspot.milkydb.client.event.RpcSuccessEventHandler;
import com.appspot.milkydb.client.service.AsyncRequest;
import com.appspot.milkydb.client.view.Waitable;
import com.google.gwt.dom.client.DivElement;
import com.google.gwt.dom.client.Document;
import com.google.gwt.dom.client.LIElement;
import com.google.gwt.dom.client.UListElement;
import com.google.gwt.event.shared.HandlerManager;
import com.google.gwt.user.client.ui.PopupPanel;

public class Wait implements Waitable {
	private PopupPanel wait;
	private List<AsyncRequest<?, ?>> requests = new ArrayList<AsyncRequest<?, ?>>();
	private final HandlerManager eventBus;

	public Wait(final HandlerManager eventBus) {
		this.eventBus = eventBus;

		bind();
	}

	@Override
	public void add(final AsyncRequest<?, ?> request) {
		requests.add(request);

		update();
	}

	private void bind() {
		eventBus.addHandler(RpcSuccessEvent.TYPE, new RpcSuccessEventHandler() {
			@Override
			public void onRpcSuccess(final RpcSuccessEvent rpcSuccessEvent) {
				update();
			}
		});

		eventBus.addHandler(RpcFailureEvent.TYPE, new RpcFailureEventHandler() {
			@Override
			public void onRpcFailure(final RpcFailureEvent rpcFailureEvent) {
				update();
			}
		});
	}

	@Override
	public void clear() {
		requests.clear();

		update();
	}

	private void removeCompleted() {
		final List<AsyncRequest<?, ?>> ans = new ArrayList<AsyncRequest<?, ?>>();
		for (final AsyncRequest<?, ?> request : requests) {
			if (!request.isCompleted()) {
				ans.add(request);
			}
		}
		requests = ans;
	}

	private void stopWait() {
		if (wait != null) {
			wait.hide();
			wait = null;
		}
	}

	private void update() {
		stopWait();

		removeCompleted();

		final boolean needWait = !requests.isEmpty();

		if (needWait) {
			final UListElement list = Document.get().createULElement();
			for (final AsyncRequest<?, ?> request : requests) {
				final LIElement li = Document.get().createLIElement();
				final DivElement div = Document.get().createDivElement();
				div.setInnerText(request.getName());
				li.appendChild(div);
				list.appendChild(li);
			}

			wait = new PopupPanel(false, true);
			wait.setTitle("Ждите...");
			wait.getElement().appendChild(list);
			wait.addStyleName("waitbox");
			wait.setGlassEnabled(true);
			wait.center();
		}
	}
}
