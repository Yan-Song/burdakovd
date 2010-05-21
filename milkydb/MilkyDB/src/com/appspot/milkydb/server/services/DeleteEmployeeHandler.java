package com.appspot.milkydb.server.services;

import com.appspot.milkydb.server.models.Employee;

public class DeleteEmployeeHandler extends
		AbstractDeleteEntitiesHandler<Employee> {

	public DeleteEmployeeHandler() {
		super(Employee.class);
	}
}
