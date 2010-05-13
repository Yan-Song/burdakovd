package com.appspot.milkydb.client.presenter;

import java.util.ArrayList;
import java.util.List;

import com.appspot.milkydb.client.event.AddEmployeeEvent;
import com.appspot.milkydb.shared.dto.LightEmployee;
import com.appspot.milkydb.shared.services.Action;
import com.appspot.milkydb.shared.services.MilkyServiceAsync;
import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.event.dom.client.HasClickHandlers;
import com.google.gwt.event.shared.HandlerManager;
import com.google.gwt.user.client.Window;
import com.google.gwt.user.client.rpc.AsyncCallback;
import com.google.gwt.user.client.ui.HasWidgets;
import com.google.gwt.user.client.ui.Widget;

public class EmployeePresenter implements Presenter {

	public interface Display {
		Widget asWidget();

		HasClickHandlers getAddButton();

		void setData(final List<LightEmployee> employees);
	}

	private final Display display;
	private final MilkyServiceAsync service;
	private final HandlerManager eventBus;

	public EmployeePresenter(final Display display,
			final MilkyServiceAsync service, final HandlerManager eventBus) {
		this.display = display;
		this.service = service;
		this.eventBus = eventBus;

		bind();
	}

	private void bind() {
		display.getAddButton().addClickHandler(new ClickHandler() {
			@Override
			public void onClick(final ClickEvent event) {
				eventBus.fireEvent(new AddEmployeeEvent());
			}
		});
	}

	private void fetchEmployeeList() {

		service.execute(Action.getLightEmployeeList, null,
				new AsyncCallback<ArrayList<LightEmployee>>() {

					@Override
					public void onFailure(final Throwable caught) {
						Window.alert("Can't fetch employee list");
					}

					@Override
					public void onSuccess(final ArrayList<LightEmployee> result) {
						display.setData(result);
					}
				});

	}

	@Override
	public void go(final HasWidgets container) {
		container.clear();
		container.add(display.asWidget());

		fetchEmployeeList();
	}
}
