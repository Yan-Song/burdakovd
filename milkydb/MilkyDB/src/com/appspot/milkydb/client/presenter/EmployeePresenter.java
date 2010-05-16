package com.appspot.milkydb.client.presenter;

import java.util.ArrayList;
import java.util.List;

import com.appspot.milkydb.client.event.AddEmployeeEvent;
import com.appspot.milkydb.client.event.EditEmployeeEvent;
import com.appspot.milkydb.client.view.Waitable;
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

	public interface Display extends Waitable {
		Widget asWidget();

		HasClickHandlers getAddButton();

		HasClickHandlers getEmployeeTable();

		int getRowIndexForEvent(ClickEvent event);

		void setData(final List<LightEmployee> employees);
	}

	private final Display display;
	private final MilkyServiceAsync service;
	private final HandlerManager eventBus;
	private ArrayList<String> keys;

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

		display.getEmployeeTable().addClickHandler(new ClickHandler() {

			@Override
			public void onClick(final ClickEvent event) {
				onTableClick(event);
			}
		});
	}

	private void fetchEmployeeList() {
		display.startWait("Загрузка списка служащих...");

		service.execute(Action.getLightEmployeeList, null,
				new AsyncCallback<ArrayList<LightEmployee>>() {

					@Override
					public void onFailure(final Throwable caught) {
						Window.alert("Can't fetch employee list");
						caught.printStackTrace();
						display.stopWait();
					}

					@Override
					public void onSuccess(final ArrayList<LightEmployee> result) {
						keys = new ArrayList<String>();
						for (final LightEmployee e : result) {
							keys.add(e.key);
						}
						display.setData(result);
						display.stopWait();
					}
				});

	}

	@Override
	public void go(final HasWidgets container) {
		container.clear();
		container.add(display.asWidget());

		fetchEmployeeList();
	}

	private void onTableClick(final ClickEvent event) {
		final int idx = display.getRowIndexForEvent(event);
		if (idx >= 0) {
			eventBus.fireEvent(new EditEmployeeEvent(keys.get(idx)));
		}
	}
}
