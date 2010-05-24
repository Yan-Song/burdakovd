package com.appspot.milkydb.server.services;

import com.appspot.milkydb.client.validation.ValidationError;
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
	protected Employee doSave(final Employee dto, final Objectify ofy)
			throws ValidationError {
		DAO.getOrCreate(Appointment.class, ofy, dto.getAppointment());
		return super.doSave(dto, ofy);
	}

	@Override
	protected void setData(final Employee employee, final Employee request) {
		employee.setName(request.getName());
		employee.setAppointment(request.getAppointment());
		employee.setSalary(request.getSalary());
		employee.setContactInfo(request.getContactInfo());
	}
}
