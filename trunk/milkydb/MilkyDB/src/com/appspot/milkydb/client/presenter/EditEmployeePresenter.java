package com.appspot.milkydb.client.presenter;

import java.util.ArrayList;

import com.appspot.milkydb.client.event.EditEmployeeFinishedEvent;
import com.appspot.milkydb.client.service.ManagedAsyncService;
import com.appspot.milkydb.client.ui.FreeListBox;
import com.appspot.milkydb.client.ui.Wait;
import com.appspot.milkydb.client.validation.CanDisplayValidationExceptions;
import com.appspot.milkydb.client.validation.ValidationException;
import com.appspot.milkydb.client.view.Waitable;
import com.appspot.milkydb.shared.dto.FullEmployee;
import com.appspot.milkydb.shared.services.Action;
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

	public interface Display extends CanDisplayValidationExceptions {
		final static String fieldName = "name";
		final static String fieldPost = "post";
		final static String fieldSalary = "salary";
		final static String fieldAddress = "address";
		final static String fieldPhoneNumber = "phoneNumber";

		final static String[] fields = new String[] { fieldName, fieldPost,
				fieldSalary, fieldAddress, fieldPhoneNumber };

		Widget asWidget();

		HasValue<String> getAddress();

		HasClickHandlers getCancelButton();

		HasValue<String> getName();

		HasValue<String> getPhoneNumber();

		FreeListBox getPost();

		HasValue<String> getSalary();

		HasClickHandlers getSubmitButton();
	}

	private final Waitable wait;
	private final Display display;
	private final ManagedAsyncService service;
	private final HandlerManager eventBus;
	private final String key;

	public EditEmployeePresenter(final Display editEmployeeView,
			final ManagedAsyncService service, final HandlerManager eventBus) {
		this(editEmployeeView, service, eventBus, null);
	}

	public EditEmployeePresenter(final Display editEmployeeView,
			final ManagedAsyncService service, final HandlerManager eventBus,
			final String key) {
		this.display = editEmployeeView;
		this.service = service;
		this.eventBus = eventBus;
		this.key = key;
		wait = new Wait(eventBus, service);

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

		display.clearErrors();
		try {
			localValidate();

			wait.add(service.execute(Action.saveEmployee, new FullEmployee(key,
					display.getName().getValue(), display.getPost().getValue(),
					Double.parseDouble(display.getSalary().getValue()), display
							.getAddress().getValue(), display.getPhoneNumber()
							.getValue()), new AsyncCallback<String>() {
				@Override
				public void onFailure(final Throwable caught) {
					if (caught instanceof ValidationException) {
						display
								.showValidationError((ValidationException) caught);
					} else {
						Window.alert("Can't save");
						caught.printStackTrace();
					}
				}

				@Override
				public void onSuccess(final String result) {
					eventBus.fireEvent(new EditEmployeeFinishedEvent());
				}
			}, "Сохранение"));
		} catch (final ValidationException e) {
			display.showValidationError(e);
		}
	}

	private void fetchEmployeeDetails() {
		wait.add(service.execute(Action.getEmployee, key,
				new AsyncCallback<FullEmployee>() {

					@Override
					public void onFailure(final Throwable caught) {
						Window.alert("Can't fetch employee info");
						caught.printStackTrace();
					}

					@Override
					public void onSuccess(final FullEmployee result) {
						displayData(result);
					}
				}, "Загрузка информации о работнике"));
	}

	@Override
	public void go(final HasWidgets container) {
		container.clear();
		container.add(display.asWidget());

		wait.add(service.execute(Action.getAppointments, null,
				new AsyncCallback<ArrayList<String>>() {
					@Override
					public void onFailure(final Throwable caught) {
						Window.alert("Can't fetch appointments list");
						caught.printStackTrace();
					}

					@Override
					public void onSuccess(final ArrayList<String> result) {
						display.getPost().setVariants(result, true);
					}
				}, "Загрузка списка должностей"));

		if (key != null) {
			fetchEmployeeDetails();
		}
	}

	private void localValidate() throws ValidationException {
		try {
			Double.parseDouble(display.getSalary().getValue());
		} catch (final NumberFormatException e) {
			throw new ValidationException(Display.fieldSalary, "Введите число");
		}
	}
}
