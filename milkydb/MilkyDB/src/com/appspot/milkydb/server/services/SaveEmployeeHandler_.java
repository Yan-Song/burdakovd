package com.appspot.milkydb.server.services;

import javax.jdo.JDOObjectNotFoundException;
import javax.jdo.PersistenceManager;
import javax.jdo.Transaction;

import com.appspot.milkydb.server.PMF;
import com.appspot.milkydb.server.models.Appointment;
import com.appspot.milkydb.server.models.ContactInfo;
import com.appspot.milkydb.server.models.Employee;
import com.appspot.milkydb.shared.dto.FullEmployee;
import com.google.appengine.api.datastore.Key;
import com.google.appengine.api.datastore.KeyFactory;

public class SaveEmployeeHandler_ implements
		ActionHandler<FullEmployee, String> {

	@Override
	public String execute(final FullEmployee request) {
		final PersistenceManager pm = PMF.get();

		try {
			getOrCreateAppointment(request.post, pm);

			final boolean newEmployee = request.key == null;

			final Transaction t = pm.currentTransaction();
			try {
				t.begin();

				final Employee employee = newEmployee ? new Employee() : pm
						.getObjectById(Employee.class, KeyFactory
								.stringToKey(request.key));

				// validate here
				// ...

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
}
