package com.appspot.milkydb.client.ui;

import java.util.ArrayList;
import java.util.List;

import com.appspot.milkydb.client.event.DelayedModeTickEvent;
import com.appspot.milkydb.client.event.DelayedModeTickEventHandler;
import com.appspot.milkydb.client.event.EnteredDelayedModeEvent;
import com.appspot.milkydb.client.event.EnteredDelayedModeEventHandler;
import com.appspot.milkydb.client.event.LeavedDelayedModeEvent;
import com.appspot.milkydb.client.event.LeavedDelayedModeEventHandler;
import com.appspot.milkydb.client.event.RpcFailureEvent;
import com.appspot.milkydb.client.event.RpcFailureEventHandler;
import com.appspot.milkydb.client.event.RpcSuccessEvent;
import com.appspot.milkydb.client.event.RpcSuccessEventHandler;
import com.appspot.milkydb.client.service.AsyncRequest;
import com.appspot.milkydb.client.service.ManagedAsyncService;
import com.google.gwt.dom.client.DivElement;
import com.google.gwt.dom.client.Document;
import com.google.gwt.dom.client.LIElement;
import com.google.gwt.dom.client.UListElement;
import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.event.shared.HandlerManager;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.FlowPanel;
import com.google.gwt.user.client.ui.HTML;
import com.google.gwt.user.client.ui.Label;
import com.google.gwt.user.client.ui.PopupPanel;
import com.google.gwt.user.client.ui.VerticalPanel;

public class Wait implements Waitable {
	private PopupPanel wait;
	private List<AsyncRequest<?, ?>> requests = new ArrayList<AsyncRequest<?, ?>>();
	private final HandlerManager eventBus;
	private final ManagedAsyncService service;

	public Wait(final HandlerManager eventBus, final ManagedAsyncService service) {
		this.eventBus = eventBus;
		this.service = service;

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

		eventBus.addHandler(EnteredDelayedModeEvent.TYPE,
				new EnteredDelayedModeEventHandler() {
					@Override
					public void onEnteredDelayedMode(
							final EnteredDelayedModeEvent enteredDelayedModeEvent) {
						update();
					}
				});

		eventBus.addHandler(LeavedDelayedModeEvent.TYPE,
				new LeavedDelayedModeEventHandler() {
					@Override
					public void onLeavedDelayedMode(
							final LeavedDelayedModeEvent leavedDelayedModeEvent) {
						update();
					}
				});

		eventBus.addHandler(DelayedModeTickEvent.TYPE,
				new DelayedModeTickEventHandler() {
					@Override
					public void onDelayedModeTick(
							final DelayedModeTickEvent delayedModeTickEvent) {
						update();

					}
				});
	}

	@Override
	public void clear() {
		requests.clear();

		update();
	}

	private void removeCompletedRequests() {
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

		removeCompletedRequests();

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
			wait.addStyleName("wait-popup-panel");
			wait.setTitle("Ждите...");
			final VerticalPanel vp = new VerticalPanel();
			wait.add(vp);
			final DivElement ld = Document.get().createDivElement();
			ld.appendChild(list);
			vp.add(new HTML(ld) {
			});

			if (service.isInDelayedMode()) {
				vp.add(new FlowPanel() {
					{
						addStyleName("delayed");
						add(new Label(
								"Связь с сервером потеряна. Повтор через "
										+ service.getSecondsBeforeNextRetry()
										+ " сек. "));
						add(new Button("Повторить сейчас") {
							{
								addClickHandler(new ClickHandler() {
									@Override
									public void onClick(final ClickEvent event) {
										service.retryNow();
									}
								});
							}
						});
					}
				});
			}

			wait.addStyleName("waitbox");
			wait.setGlassEnabled(true);
			wait.center();
		}
	}
}
