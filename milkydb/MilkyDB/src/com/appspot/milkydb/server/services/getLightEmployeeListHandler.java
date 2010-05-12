package com.appspot.milkydb.server.services;

import java.util.ArrayList;
import java.util.List;

import javax.jdo.PersistenceManager;

import com.appspot.milkydb.server.PMF;
import com.appspot.milkydb.server.Models.Employee;
import com.appspot.milkydb.shared.services.SerializableVoid;
import com.appspot.milkydb.shared.transferObjects.LightEmployee;
import com.google.appengine.repackaged.com.google.common.base.Function;
import com.google.appengine.repackaged.com.google.common.collect.Lists;

public class getLightEmployeeListHandler implements
		ActionHandler<SerializableVoid, ArrayList<LightEmployee>> {

	@SuppressWarnings("unchecked")
	@Override
	public ArrayList<LightEmployee> execute(final SerializableVoid _) {

		final PersistenceManager pm = PMF.get();
		final javax.jdo.Query query = pm.newQuery(Employee.class);
		query.setOrdering("name asc");

		return new ArrayList<LightEmployee>(Lists.transform(
				(List<Employee>) query.execute(),
				new Function<Employee, LightEmployee>() {

					@Override
					public LightEmployee apply(final Employee employee) {
						return new LightEmployee(employee.getName(), employee
								.getAppointment().getName(), employee
								.getSalary());
					}
				}));
	}
}
