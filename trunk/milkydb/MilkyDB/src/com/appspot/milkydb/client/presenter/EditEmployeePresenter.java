package com.appspot.milkydb.client.presenter;

import java.util.ArrayList;

import com.appspot.milkydb.client.event.EditEmployeeFinishedEvent;
import com.appspot.milkydb.client.service.ManagedAsyncService;
import com.appspot.milkydb.client.ui.FreeListBox;
import com.appspot.milkydb.client.validation.ValidationError;
import com.appspot.milkydb.shared.dto.FullEmployee;
import com.appspot.milkydb.shared.service.Action;
import com.google.gwt.event.shared.HandlerManager;
import com.google.gwt.user.client.Window;
import com.google.gwt.user.client.rpc.AsyncCallback;
import com.google.gwt.user.client.ui.HasValue;
import com.google.gwt.user.client.ui.HasWidgets;

public class EditEmployeePresenter extends AbstractEditPresenter<FullEmployee> {

	public interface Display extends AbstractEditPresenter.Display {
		HasValue<String> getAddress();

		HasValue<String> getName();

		HasValue<String> getPhoneNumber();

		FreeListBox getPost();

		HasValue<String> getSalary();
	}

	private final Display display;

	public EditEmployeePresenter(final Display display,
			final ManagedAsyncService service, final HandlerManager eventBus) {
		this(display, service, eventBus, null);
	}

	public EditEmployeePresenter(final Display display,
			final ManagedAsyncService service, final HandlerManager eventBus,
			final String key) {
		super(display, service, eventBus, key);
		this.display = display;
	}

	@Override
	protected void displayDto(final FullEmployee data) {
		display.getName().setValue(data.name);
		display.getPost().setValue(data.post);
		display.getSalary().setValue(data.salary.toString());
		display.getAddress().setValue(data.address);
		display.getPhoneNumber().setValue(data.phone);
	}

	private void fetchAppointments() {
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
	}

	@Override
	protected void fireEditFinishedEvent() {
		eventBus.fireEvent(new EditEmployeeFinishedEvent());
	}

	@Override
	public void go(final HasWidgets container) {
		super.go(container);
		fetchAppointments();
	}

	@Override
	protected FullEmployee makeDto() throws ValidationError {
		double salary;

		try {
			salary = Double.parseDouble(display.getSalary().getValue());
		} catch (final NumberFormatException e) {
			throw new ValidationError(FullEmployee.Fields.salary,
					"Введите число");
		}

		return new FullEmployee(key, display.getName().getValue(), display
				.getPost().getValue(), salary, display.getAddress().getValue(),
				display.getPhoneNumber().getValue());
	}

	@Override
	protected Action<String, FullEmployee> provideGetEntityAction() {
		return Action.getEmployee;
	}

	@Override
	protected Action<FullEmployee, String> provideSaveEntityAction() {
		return Action.saveEmployee;
	}
}