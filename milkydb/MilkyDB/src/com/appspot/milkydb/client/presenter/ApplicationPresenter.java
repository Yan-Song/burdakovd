package com.appspot.milkydb.client.presenter;

import java.util.ArrayList;
import java.util.List;

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
import com.appspot.milkydb.client.view.RawMaterialClassesView;
import com.google.gwt.event.logical.shared.ValueChangeEvent;
import com.google.gwt.event.logical.shared.ValueChangeHandler;
import com.google.gwt.event.shared.HandlerManager;
import com.google.gwt.user.client.History;
import com.google.gwt.user.client.Window;
import com.google.gwt.user.client.ui.HasWidgets;
import com.google.gwt.user.client.ui.Widget;

@SuppressWarnings("serial")
public class ApplicationPresenter implements Presenter,
		ValueChangeHandler<String> {

	public interface Display {
		Widget asWidget();

		HasWidgets getContentPanel();

		HasWidgets getNavigationPanel();
	}

	private abstract class EntityManager {
		String prefix;

		public EntityManager(final String prefix) {
			this.prefix = prefix;
		}

		abstract Presenter getEditPresenter(String key);

		abstract Presenter getListPresenter();

		abstract Presenter getNewPresenter();
	}

	static final String defaultHistoryToken = "home";
	private final HandlerManager eventBus;

	private final ManagedAsyncService service;

	private final Display display;
	private final List<EntityManager> entityManagers = new ArrayList<EntityManager>() {
		{
			add(new EntityManager("employee") {

				@Override
				public Presenter getEditPresenter(final String key) {
					return new EditEmployeePresenter(new EditEmployeeView(),
							service, eventBus, key);
				}

				@Override
				public Presenter getListPresenter() {
					return new EmployeePresenter(new EmployeeView(), service,
							eventBus);
				}

				@Override
				public Presenter getNewPresenter() {
					return new EditEmployeePresenter(new EditEmployeeView(),
							service, eventBus);
				}
			});

			add(new EntityManager("rawMaterialsClasses") {

				@Override
				public Presenter getEditPresenter(final String key) {
					// TODO Auto-generated method stub
					return null;
				}

				@Override
				public Presenter getListPresenter() {
					return new RawMaterialClassesPresenter(
							new RawMaterialClassesView(), service, eventBus);
				}

				@Override
				public Presenter getNewPresenter() {
					// TODO Auto-generated method stub
					return null;
				}
			});
		}
	};

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

		if (token.equals("home")) {
			presenter = new HomePresenter(new HomeView());
		} else {
			for (final EntityManager manager : entityManagers) {
				if (token.equals(manager.prefix)) {
					presenter = manager.getListPresenter();
				} else if (token.equals(manager.prefix + "/new")) {
					presenter = manager.getNewPresenter();
				} else {
					final String prefix = manager.prefix + "/edit/";
					if (token.startsWith(prefix)) {
						final String key = token.substring(prefix.length());
						presenter = manager.getEditPresenter(key);
					}
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
