package com.appspot.milkydb.client.presenter;

import java.util.ArrayList;

import com.appspot.milkydb.client.event.EditEmployeeFinishedEvent;
import com.appspot.milkydb.client.ui.FreeListBox;
import com.appspot.milkydb.client.view.Waitable;
import com.appspot.milkydb.shared.dto.FullEmployee;
import com.appspot.milkydb.shared.services.Action;
import com.appspot.milkydb.shared.services.MilkyServiceAsync;
import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.event.dom.client.HasClickHandlers;
import com.google.gwt.event.shared.HandlerManager;
import com.google.gwt.user.client.Window;
import com.google.gwt.user.client.rpc.AsyncCallback;
import com.google.gwt.user.client.ui.HasValue;
import com.google.gwt.user.client.ui.HasWidgets;
import com.google.gwt.user.client.ui.Widget;

public class EditEmployeePresenter implements Presenter {

	public interface Display extends Waitable {
		Widget asWidget();

		HasValue<String> getAddress();

		HasClickHandlers getCancelButton();

		HasValue<String> getName();

		HasValue<String> getPhoneNumber();

		FreeListBox getPost();

		HasValue<String> getSalary();

		HasClickHandlers getSubmitButton();
	}

	private final Display display;
	private final MilkyServiceAsync service;
	private final HandlerManager eventBus;
	private final String key;

	/*
	 * добавление служащего
	 */
	public EditEmployeePresenter(final Display editEmployeeView,
			final MilkyServiceAsync service, final HandlerManager eventBus) {
		this(editEmployeeView, service, eventBus, null);
	}

	public EditEmployeePresenter(final Display editEmployeeView,
			final MilkyServiceAsync service, final HandlerManager eventBus,
			final String key) {
		this.display = editEmployeeView;
		this.service = service;
		this.eventBus = eventBus;
		this.key = key;

		bind();
	}

	private void bind() {
		display.getCancelButton().addClickHandler(new ClickHandler() {
			@Override
			public void onClick(final ClickEvent event) {
				eventBus.fireEvent(new EditEmployeeFinishedEvent());
			}
		});

		display.getSubmitButton().addClickHandler(new ClickHandler() {
			@Override
			public void onClick(final ClickEvent event) {
				doSubmit();
			}
		});
	}

	private void displayData(final FullEmployee data) {
		display.getName().setValue(data.name);
		display.getPost().setValue(data.post);
		display.getSalary().setValue(data.salary.toString());
		display.getAddress().setValue(data.address);
		display.getPhoneNumber().setValue(data.phone);
	}

	private void doSubmit() {
		display.startWait("Сохранение");

		// тут может быть клиентская валидация
		// ...

		service.execute(Action.saveEmployee, new FullEmployee(key, display
				.getName().getValue(), display.getPost().getValue(), Double
				.parseDouble(display.getSalary().getValue()), display
				.getAddress().getValue(), display.getPhoneNumber().getValue()),
				new AsyncCallback<String>() {
					@Override
					public void onFailure(final Throwable caught) {
						Window.alert("can't save");
						display.stopWait();
						caught.printStackTrace();
					}

					@Override
					public void onSuccess(final String result) {
						display.stopWait();
						eventBus.fireEvent(new EditEmployeeFinishedEvent());
					}
				});
	}

	private void fetchEmployeeDetails() {
		display.startWait("Загрузка информации о работнике");

		service.execute(Action.getEmployee, key,
				new AsyncCallback<FullEmployee>() {

					@Override
					public void onFailure(final Throwable caught) {
						Window.alert("Can't fetch employee info");
						caught.printStackTrace();
						display.stopWait();
					}

					@Override
					public void onSuccess(final FullEmployee result) {
						displayData(result);
						display.stopWait();
					}
				});
	}

	@Override
	public void go(final HasWidgets container) {
		container.clear();
		container.add(display.asWidget());

		display.startWait("Загрузка списка должностей");
		service.execute(Action.getAppointments, null,
				new AsyncCallback<ArrayList<String>>() {
					@Override
					public void onFailure(final Throwable caught) {
						Window.alert("Can't fetch appointments list");
						caught.printStackTrace();
						display.stopWait();
					}

					@Override
					public void onSuccess(final ArrayList<String> result) {
						display.getPost().setVariants(result, true);
						display.stopWait();

						if (key != null) {
							fetchEmployeeDetails();
						}
					}
				});
	}
}
