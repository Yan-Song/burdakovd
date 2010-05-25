package com.appspot.milkydb.server.services;

import com.appspot.milkydb.server.DAO;
import com.appspot.milkydb.shared.models.Appointment;
import com.appspot.milkydb.shared.models.Employee;
import com.googlecode.objectify.Objectify;

public class SaveEmployeeHandler extends
		AbstractSaveEntityHandler<Employee, Employee> {

	public SaveEmployeeHandler() {
		super(Employee.class);
	}

	@Override
	protected void setData(final Objectify ofy, final Employee employee,
			final Employee request) {

		DAO.updateDictionaryFields(ofy, Appointment.class, employee
				.getAppointment(), request.getAppointment());

		employee.setName(request.getName());
		employee.setAppointment(request.getAppointment());
		employee.setSalary(request.getSalary());
		employee.setContactInfo(request.getContactInfo());
	}

}
