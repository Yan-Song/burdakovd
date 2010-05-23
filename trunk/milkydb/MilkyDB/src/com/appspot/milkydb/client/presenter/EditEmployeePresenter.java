package com.appspot.milkydb.client.presenter;

import java.util.ArrayList;

import com.appspot.milkydb.client.service.ManagedAsyncService;
import com.appspot.milkydb.client.ui.FreeListBox;
import com.appspot.milkydb.client.validation.ValidationError;
import com.appspot.milkydb.shared.dto.DtoList;
import com.appspot.milkydb.shared.dto.SingleKey;
import com.appspot.milkydb.shared.models.Appointment;
import com.appspot.milkydb.shared.models.ContactInfo;
import com.appspot.milkydb.shared.models.Employee;
import com.appspot.milkydb.shared.service.action.Action;
import com.appspot.milkydb.shared.service.action.ManagerActionSet;
import com.google.gwt.event.shared.HandlerManager;
import com.google.gwt.user.client.Window;
import com.google.gwt.user.client.rpc.AsyncCallback;
import com.google.gwt.user.client.ui.HasValue;
import com.google.gwt.user.client.ui.HasWidgets;

public class EditEmployeePresenter extends AbstractEditPresenter<Employee> {

	public interface Display extends AbstractEditPresenter.Display {
		HasValue<String> getAddress();

		HasValue<String> getName();

		HasValue<String> getPhoneNumber();

		FreeListBox getPost();

		HasValue<String> getSalary();
	}

	private final Display display;

	public EditEmployeePresenter(final Display display,
			final ManagedAsyncService service,
			final HandlerManager localEventBus, final HandlerManager eventBus) {
		this(display, service, localEventBus, eventBus, null);
	}

	public EditEmployeePresenter(final Display display,
			final ManagedAsyncService service,
			final HandlerManager localEventBus, final HandlerManager eventBus,
			final SingleKey key) {
		super(display, service, localEventBus, eventBus, key);
		this.display = display;
	}

	@Override
	protected void displayDto(final Employee data) {
		display.getName().setValue(data.getName());
		display.getPost().setValue(data.getAppointment());
		display.getSalary().setValue(String.valueOf(data.getSalary()));
		display.getAddress().setValue(
				data.getContactInfo().getAddress().toString());
		display.getPhoneNumber().setValue(
				data.getContactInfo().getPhoneNumber());
	}

	private void fetchAppointments() {
		wait.add(service.execute(Action.getAppointments, null,
				new AsyncCallback<DtoList<Appointment>>() {
					@Override
					public void onFailure(final Throwable caught) {
						Window.alert("Can't fetch appointments list");
						caught.printStackTrace();
					}

					@Override
					public void onSuccess(final DtoList<Appointment> result) {
						final ArrayList<String> variants = new ArrayList<String>();
						for (final Appointment a : result) {
							variants.add(a.getName());
						}
						display.getPost().setVariants(variants, true);
					}
				}, "Загрузка списка должностей"));
	}

	@Override
	public void go(final HasWidgets container) {
		super.go(container);
		fetchAppointments();
	}

	@Override
	protected Employee makeDto() throws ValidationError {
		double salary;

		try {
			salary = Double.parseDouble(display.getSalary().getValue());
		} catch (final NumberFormatException e) {
			throw new ValidationError(Employee.Fields.salary, "Введите число");
		}

		final ContactInfo contactInfo = new ContactInfo(display.getAddress()
				.getValue(), display.getPhoneNumber().getValue());
		return new Employee(key == null ? null : key.getValue(), display
				.getName().getValue(), contactInfo, display.getPost()
				.getValue(), salary);
	}

	@Override
	protected Action<SingleKey, Employee> provideGetEntityAction() {
		return ManagerActionSet.Employee.provideGetAction();
	}

	@Override
	protected Action<Employee, SingleKey> provideSaveEntityAction() {
		return ManagerActionSet.Employee.provideSaveAction();
	}
}
