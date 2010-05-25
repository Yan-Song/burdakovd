/**
 * 
 */
package com.appspot.milkydb.server.services;

import java.util.Collection;
import java.util.HashMap;
import java.util.Map;

import com.appspot.milkydb.server.DAO;
import com.appspot.milkydb.shared.models.Appointment;
import com.appspot.milkydb.shared.models.Employee;
import com.googlecode.objectify.Key;
import com.googlecode.objectify.Objectify;

/**
 * @author burdakovd
 * 
 */
public class DeleteEmployeeHandler extends
		SimpleDeleteEntitiesHandler<Employee> {

	/**
	 * @param modelClass
	 */
	public DeleteEmployeeHandler() {
		super(Employee.class);
	}

	@Override
	protected void beforeDelete(final DAO dao, final Objectify t,
			final Iterable<Key<Employee>> tKeys) {

		final Collection<Employee> entities = t.get(tKeys).values();
		final Map<String, Integer> removedAppointments = new HashMap<String, Integer>();

		for (final Employee entity : entities) {
			final String appointment = entity.getAppointment();
			removedAppointments.put(appointment, (removedAppointments
					.containsKey(appointment) ? removedAppointments
					.get(appointment) : 0) + 1);
		}

		DAO.decrementAndDeleteIfNotUsed(t, Appointment.class,
				removedAppointments);

		super.beforeDelete(dao, t, tKeys);
	}
}
