package com.appspot.milkydb.server.services;

import com.appspot.milkydb.shared.models.Employee;

public class DeleteEmployeeHandler extends
		AbstractDeleteEntitiesHandler<Employee> {

	public DeleteEmployeeHandler() {
		super(Employee.class);
	}
}
