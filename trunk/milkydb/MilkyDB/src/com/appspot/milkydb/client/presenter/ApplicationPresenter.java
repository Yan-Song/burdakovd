package com.appspot.milkydb.client.presenter;

import com.appspot.milkydb.client.event.AddEmployeeEvent;
import com.appspot.milkydb.client.event.AddEmployeeEventHandler;
import com.appspot.milkydb.client.event.EditEmployeeEvent;
import com.appspot.milkydb.client.event.EditEmployeeEventHandler;
import com.appspot.milkydb.client.event.EditEmployeeFinishedEvent;
import com.appspot.milkydb.client.event.EditEmployeeFinishedEventHandler;
import com.appspot.milkydb.client.service.ManagedAsyncService;
import com.appspot.milkydb.client.view.EditEmployeeView;
import com.appspot.milkydb.client.view.EmployeeView;
import com.appspot.milkydb.client.view.HomeView;
import com.appspot.milkydb.client.view.NavigationView;
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
	private final ManagedAsyncService service;

	private final Display display;

	public ApplicationPresenter(final HandlerManager eventBus,
			final ManagedAsyncService service, final Display display) {

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

		eventBus.addHandler(AddEmployeeEvent.TYPE,
				new AddEmployeeEventHandler() {
					@Override
					public void onAddEmployee(
							final AddEmployeeEvent addEmployeeEvent) {
						History.newItem("employee/new");
					}
				});

		eventBus.addHandler(EditEmployeeEvent.TYPE,
				new EditEmployeeEventHandler() {

					@Override
					public void onEditEmployee(
							final EditEmployeeEvent editEmployeeEvent) {
						History.newItem("employee/edit/"
								+ editEmployeeEvent.getKey());
					}
				});

		eventBus.addHandler(EditEmployeeFinishedEvent.TYPE,
				new EditEmployeeFinishedEventHandler() {
					@Override
					public void onEditEmployeeFinished(
							final EditEmployeeFinishedEvent editEmployeeFinishedEvent) {
						History.newItem("employee");
					}
				});
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

		final String editEmployeePrefix = "employee/edit/";

		if (token.equals("home")) {
			presenter = new HomePresenter(new HomeView());
		} else if (token.equals("employee")) {
			presenter = new EmployeePresenter(new EmployeeView(), service,
					eventBus);
		} else if (token.equals("employee/new")) {
			presenter = new EditEmployeePresenter(new EditEmployeeView(),
					service, eventBus);
		} else if (token.startsWith(editEmployeePrefix)) {
			presenter = new EditEmployeePresenter(new EditEmployeeView(),
					service, eventBus, token.substring(editEmployeePrefix
							.length()));
		}

		if (presenter == null) {
			Window.alert("Page \"" + token
					+ "\" not found. Redirecting to default page...");
			History.newItem(defaultHistoryToken);
		} else {
			presenter.go(display.getContentPanel());
		}
	}
}