package com.appspot.milkydb.server.services;

import javax.jdo.JDOObjectNotFoundException;
import javax.jdo.PersistenceManager;
import javax.jdo.Transaction;

import com.appspot.milkydb.client.validation.ValidationException;
import com.appspot.milkydb.server.PMF;
import com.appspot.milkydb.server.models.Appointment;
import com.appspot.milkydb.server.models.ContactInfo;
import com.appspot.milkydb.server.models.Employee;
import com.appspot.milkydb.shared.dto.FullEmployee;
import com.google.appengine.api.datastore.Key;
import com.google.appengine.api.datastore.KeyFactory;

public class SaveEmployeeHandler extends
		AbstractSaveEntityHandler<Employee, FullEmployee> {

	public SaveEmployeeHandler() {
		super(Employee.class);
	}

	@Override
	public String execute(final FullEmployee request)
			throws ValidationException {
		request.validate();

		final PersistenceManager pm = PMF.get();
		try {
			getOrCreateAppointment(request.post, pm);
		} finally {
			pm.close();
		}

		return super.execute(request);
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

	@Override
	protected void setData(final Employee employee, final FullEmployee request) {
		employee.setName(request.name);
		employee.setAppointment(request.post);
		employee.setSalary(request.salary);
		employee
				.setContactInfo(new ContactInfo(request.address, request.phone));
	}
}
