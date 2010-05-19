package com.appspot.milkydb.server.services;

import javax.jdo.PersistenceManager;

import com.appspot.milkydb.server.PMF;
import com.appspot.milkydb.server.models.Employee;
import com.appspot.milkydb.shared.dto.FullEmployee;
import com.google.appengine.api.datastore.KeyFactory;

public class GetEmployeeHandler implements ActionHandler<String, FullEmployee> {

	@Override
	public FullEmployee execute(final String request) {
		final PersistenceManager pm = PMF.get();

		try {
			final Employee employee = pm.getObjectById(Employee.class,
					KeyFactory.stringToKey(request));

			return new FullEmployee(KeyFactory.keyToString(employee.getKey()),
					employee.getName(), employee.getAppointment(), employee
							.getSalary(), employee.getContactInfo()
							.getAddress().getValue(), employee.getContactInfo()
							.getPhoneNumber());
		} finally {
			pm.close();
		}
	}
}
