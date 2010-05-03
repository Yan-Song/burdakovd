package com.appspot.milkydb.client.presenter;

import com.appspot.milkydb.client.view.HomeView;
import com.appspot.milkydb.client.view.NavigationView;
import com.appspot.milkydb.shared.MilkyServiceAsync;
import com.google.gwt.event.logical.shared.ValueChangeEvent;
import com.google.gwt.event.logical.shared.ValueChangeHandler;
import com.google.gwt.event.shared.HandlerManager;
import com.google.gwt.user.client.History;
import com.google.gwt.user.client.Window;
import com.google.gwt.user.client.ui.HasWidgets;
import com.google.gwt.user.client.ui.Widget;

public class ApplicationPresenter implements Presenter,
		ValueChangeHandler<String> {

	public interface Display {
		Widget asWidget();

		HasWidgets getContentPanel();

		HasWidgets getNavigationPanel();
	}

	static final String defaultHistoryToken = "home";

	private final HandlerManager eventBus;
	private final MilkyServiceAsync service;

	private final Display display;

	public ApplicationPresenter(final HandlerManager eventBus,
			final MilkyServiceAsync service, final Display display) {

		this.eventBus = eventBus;
		this.service = service;
		this.display = display;

		final NavigationPresenter navigator = new NavigationPresenter(
				new NavigationView());
		navigator.go(display.getNavigationPanel());

		bind();
	}

	private void bind() {
		History.addValueChangeHandler(this);
	}

	@Override
	public void go(final HasWidgets container) {
		container.clear();
		container.add(display.asWidget());

		if ("".equals(History.getToken())) {
			History.newItem(defaultHistoryToken);
		} else {
			History.fireCurrentHistoryState();
		}
	}

	@Override
	public void onValueChange(final ValueChangeEvent<String> event) {
		final String token = History.getToken();

		Presenter presenter = null;

		if (token.equals("home")) {
			presenter = new HomePresenter(new HomeView());
		}

		if (presenter == null) {
			Window.alert("Page " + token
					+ " not found. Redirecting to default page...");
			History.newItem(defaultHistoryToken);
		} else {
			presenter.go(display.getContentPanel());
		}
	}
}
