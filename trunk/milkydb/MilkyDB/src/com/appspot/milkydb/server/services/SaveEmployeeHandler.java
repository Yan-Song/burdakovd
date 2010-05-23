package com.appspot.milkydb.server.services;

import com.appspot.milkydb.server.DAO;
import com.appspot.milkydb.shared.models.Appointment;
import com.appspot.milkydb.shared.models.Employee;
import com.googlecode.objectify.Key;
import com.googlecode.objectify.NotFoundException;
import com.googlecode.objectify.Objectify;

public class SaveEmployeeHandler extends
		AbstractSaveEntityHandler<Employee, Employee> {

	public SaveEmployeeHandler() {
		super(Employee.class);
	}

	@Override
	protected Employee doSave(final Employee dto, final Objectify ofy) {

		getOrCreateAppointment(ofy, dto.getAppointment());

		return super.doSave(dto, ofy);
	}

	private Appointment getOrCreateAppointment(final Objectify ofy,
			final String appointmentName) {

		final Key<Appointment> key = new Key<Appointment>(DAO.rootKey,
				Appointment.class, appointmentName);

		Appointment appointment;

		try {
			appointment = ofy.get(key);
		} catch (final NotFoundException e) {
			appointment = new Appointment();
			appointment.setOwner(DAO.rootKey);
			appointment.setName(appointmentName);
			ofy.put(appointment);
		}

		return appointment;
	}

	@Override
	protected void setData(final Employee employee, final Employee request) {
		employee.setName(request.getName());
		employee.setAppointment(request.getAppointment());
		employee.setSalary(request.getSalary());
		employee.setContactInfo(request.getContactInfo());
	}
}
