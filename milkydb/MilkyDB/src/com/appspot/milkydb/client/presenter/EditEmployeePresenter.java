package com.appspot.milkydb.client.presenter;

import java.util.ArrayList;

import com.appspot.milkydb.client.service.ManagedAsyncService;
import com.appspot.milkydb.client.ui.FreeListBox;
import com.appspot.milkydb.client.validation.ValidationError;
import com.appspot.milkydb.shared.dto.DtoList;
import com.appspot.milkydb.shared.dto.EncodedKey;
import com.appspot.milkydb.shared.dto.FullEmployee;
import com.appspot.milkydb.shared.dto.LightAppointment;
import com.appspot.milkydb.shared.service.action.Action;
import com.appspot.milkydb.shared.service.action.ManagerActionSet;
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
			final ManagedAsyncService service,
			final HandlerManager localEventBus, final HandlerManager eventBus) {
		this(display, service, localEventBus, eventBus, null);
	}

	public EditEmployeePresenter(final Display display,
			final ManagedAsyncService service,
			final HandlerManager localEventBus, final HandlerManager eventBus,
			final EncodedKey key) {
		super(display, service, localEventBus, eventBus, key);
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
				new AsyncCallback<DtoList<LightAppointment>>() {
					@Override
					public void onFailure(final Throwable caught) {
						Window.alert("Can't fetch appointments list");
						caught.printStackTrace();
					}

					@Override
					public void onSuccess(final DtoList<LightAppointment> result) {
						final ArrayList<String> variants = new ArrayList<String>();
						for (final LightAppointment a : result) {
							variants.add(a.getAppointment());
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
	protected Action<EncodedKey, FullEmployee> provideGetEntityAction() {
		return ManagerActionSet.Employee.provideGetAction();
	}

	@Override
	protected Action<FullEmployee, EncodedKey> provideSaveEntityAction() {
		return ManagerActionSet.Employee.provideSaveAction();
	}
}
