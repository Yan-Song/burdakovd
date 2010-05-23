package com.appspot.milkydb.server.services;

import com.appspot.milkydb.shared.models.Employee;

public class GetEmployeeHandler extends
		AbstractGetEntityHandler<Employee, Employee> {

	public GetEmployeeHandler() {
		super(Employee.class);
	}

	@Override
	protected Employee makeDto(final Employee employee) {

		return employee;
	}
}
