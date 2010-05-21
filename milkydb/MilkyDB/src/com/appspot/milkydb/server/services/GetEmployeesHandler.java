package com.appspot.milkydb.server.services;

import javax.jdo.Query;

import com.appspot.milkydb.server.models.Employee;
import com.appspot.milkydb.shared.dto.EncodedKey;
import com.appspot.milkydb.shared.dto.LightEmployee;
import com.google.appengine.api.datastore.KeyFactory;

public class GetEmployeesHandler extends
		AbstractGetEntitiesHandler<Employee, LightEmployee> {

	public GetEmployeesHandler() {
		super(Employee.class);
	}

	@Override
	protected LightEmployee makeLightDto(final Employee employee) {
		return new LightEmployee(new EncodedKey(KeyFactory.keyToString(employee
				.getKey())), employee.getName(), employee.getAppointment(),
				employee.getSalary());
	}

	@Override
	protected void setOrdering(final Query query) {
		query.setOrdering("name asc");
	}
}
