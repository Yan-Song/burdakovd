package com.appspot.milkydb.server.services;

import com.appspot.milkydb.server.models.Employee;
import com.appspot.milkydb.shared.dto.FullEmployee;
import com.google.appengine.api.datastore.KeyFactory;

public class GetEmployeeHandler extends
		AbstractGetEntityHandler<Employee, FullEmployee> {

	public GetEmployeeHandler() {
		super(Employee.class);
	}

	@Override
	protected FullEmployee makeDto(final Employee employee) {
		return new FullEmployee(KeyFactory.keyToString(employee.getKey()),
				employee.getName(), employee.getAppointment(), employee
						.getSalary(), employee.getContactInfo().getAddress()
						.getValue(), employee.getContactInfo().getPhoneNumber());
	}
}
