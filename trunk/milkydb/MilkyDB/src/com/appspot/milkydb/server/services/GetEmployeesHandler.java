package com.appspot.milkydb.server.services;

import com.appspot.milkydb.shared.dto.LightEmployee;
import com.appspot.milkydb.shared.dto.SingleKey;
import com.appspot.milkydb.shared.models.Employee;

public class GetEmployeesHandler extends
		AbstractGetEntitiesHandler<Employee, LightEmployee> {

	public GetEmployeesHandler() {
		super(Employee.class);
	}

	@Override
	protected String getOrdering() {
		return "name";
	}

	@Override
	protected LightEmployee makeLightDto(final Employee employee) {
		return new LightEmployee(new SingleKey(employee.getKey()).getValue(),
				employee.getName(), employee.getAppointment(), employee
						.getSalary());
	}

}
