package com.appspot.milkydb.client;

import java.util.ArrayList;
import java.util.List;

import com.appspot.milkydb.client.entityManagers.AbstractEntityManager;
import com.appspot.milkydb.client.entityManagers.EmployeeManager;
import com.appspot.milkydb.client.entityManagers.FinalProductClassManager;
import com.appspot.milkydb.client.entityManagers.FinalProductResellerManager;
import com.appspot.milkydb.client.entityManagers.RawMaterialClassManager;
import com.appspot.milkydb.client.entityManagers.RawMaterialProviderManager;
import com.appspot.milkydb.client.presenter.HomePresenter;
import com.appspot.milkydb.client.presenter.NavigationPresenter;
import com.appspot.milkydb.client.presenter.Presenter;
import com.appspot.milkydb.client.service.ManagedAsyncService;
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

	private static final String defaultHistoryToken = "home";

	private final HandlerManager eventBus;
	private final ManagedAsyncService service;
	private final Display display;
	private final List<AbstractEntityManager> entityManagers = new ArrayList<AbstractEntityManager>();

	private final NavigationPresenter navigator;

	public ApplicationPresenter(final HandlerManager eventBus,
			final ManagedAsyncService service, final Display display) {

		this.eventBus = eventBus;
		this.service = service;
		this.display = display;

		navigator = new NavigationPresenter(new NavigationView());
		navigator.go(display.getNavigationPanel());

		bind();

		initializeEntityManagers();
	}

	private void addEntityManager(final AbstractEntityManager manager,
			final String name) {
		entityManagers.add(manager);
		navigator.addEntityManager(manager, name);
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

	private void initializeEntityManagers() {
		addEntityManager(new EmployeeManager(service, eventBus), "Служащие");
		addEntityManager(new RawMaterialClassManager(service, eventBus),
				"Классы сырья");
		addEntityManager(new FinalProductClassManager(service, eventBus),
				"Классы готовой продукции");
		addEntityManager(new RawMaterialProviderManager(service, eventBus),
				"Поставщики сырья");
		addEntityManager(new FinalProductResellerManager(service, eventBus),
				"Покупатели готовой продукции");
	}

	@Override
	public void onValueChange(final ValueChangeEvent<String> event) {
		final String token = History.getToken();

		Presenter presenter = null;

		if (token.equals("home")) {
			presenter = new HomePresenter(new HomeView());
		} else {
			for (final AbstractEntityManager manager : entityManagers) {
				final Presenter candidate = manager.getPresenter(token);
				if (candidate != null) {
					presenter = candidate;
					break;
				}
			}
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
