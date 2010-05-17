package com.appspot.milkydb.server.services;

import java.util.HashMap;

import javax.jdo.JDOObjectNotFoundException;
import javax.jdo.PersistenceManager;
import javax.jdo.Transaction;

import com.appspot.milkydb.client.presenter.EditEmployeePresenter;
import com.appspot.milkydb.client.validation.ValidationException;
import com.appspot.milkydb.client.validation.Validator;
import com.appspot.milkydb.server.PMF;
import com.appspot.milkydb.server.models.Appointment;
import com.appspot.milkydb.server.models.ContactInfo;
import com.appspot.milkydb.server.models.Employee;
import com.appspot.milkydb.shared.dto.FullEmployee;
import com.google.appengine.api.datastore.Key;
import com.google.appengine.api.datastore.KeyFactory;

public class SaveEmployeeHandler implements ActionHandler<FullEmployee, String> {

	@Override
	public String execute(final FullEmployee request)
			throws ValidationException {
		final PersistenceManager pm = PMF.get();

		try {
			validate(request);

			getOrCreateAppointment(request.post, pm);

			final boolean newEmployee = request.key == null;

			final Transaction t = pm.currentTransaction();
			try {
				t.begin();

				final Employee employee = newEmployee ? new Employee() : pm
						.getObjectById(Employee.class, KeyFactory
								.stringToKey(request.key));

				employee.setName(request.name);
				employee.setAppointment(request.post);
				employee.setSalary(request.salary);
				employee.setContactInfo(new ContactInfo(request.address,
						request.phone));
				pm.makePersistent(employee);

				t.commit();

				return KeyFactory.keyToString(employee.getKey());

			} finally {
				if (t.isActive()) {
					t.rollback();
				}
			}
		} finally {
			pm.close();
		}
	}

	private Appointment getOrCreateAppointment(final String appointmentName,
			final PersistenceManager pm) {

		final Key key = KeyFactory.createKey(Appointment.class.getSimpleName(),
				appointmentName);
		Appointment appointment;
		final Transaction t = pm.currentTransaction();
		try {
			t.begin();

			try {
				appointment = pm.getObjectById(Appointment.class, key);
			} catch (final JDOObjectNotFoundException e) {
				appointment = new Appointment();
				appointment.setKey(key);
				pm.makePersistent(appointment);
			}

			t.commit();
		} finally {
			if (t.isActive()) {
				t.rollback();
			}
		}

		return appointment;
	}

	private void validate(final FullEmployee request)
			throws ValidationException {

		final HashMap<String, String> errors = new HashMap<String, String>();

		if (!Validator.validateString(request.name, 1, 50)) {
			errors.put(EditEmployeePresenter.Display.fieldName,
					"Имя должно быть непустой строкой не длиннее 50 символов");
		}

		if (!Validator.validateString(request.post, 1, 50)) {
			errors
					.put(EditEmployeePresenter.Display.fieldPost,
							"Должность должна быть непустой строкой не длиннее 50 символов");
		}

		if (!Validator.validateDouble(request.salary, 0.0, 1000000.0)) {
			errors.put(EditEmployeePresenter.Display.fieldSalary,
					"Оклад должен быть положительным числом");
		}

		if (!Validator.validateString(request.address, 1, 500)) {
			errors
					.put(EditEmployeePresenter.Display.fieldAddress,
							"Адрес должен быть непустой строкой не длиннее 500 символов");
		}

		if (!Validator.validateString(request.phone, 1, 50)) {
			errors
					.put(EditEmployeePresenter.Display.fieldPhoneNumber,
							"Телефон должен быть непустой строкой не длиннее 50 символов");
		}

		if (!errors.isEmpty()) {
			throw new ValidationException(errors);
		}
	}
}
