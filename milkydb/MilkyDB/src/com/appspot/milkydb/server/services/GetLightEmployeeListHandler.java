package com.appspot.milkydb.server.services;

import java.util.ArrayList;
import java.util.List;

import javax.jdo.PersistenceManager;

import com.appspot.milkydb.server.PMF;
import com.appspot.milkydb.server.models.Employee;
import com.appspot.milkydb.shared.dto.LightEmployee;
import com.appspot.milkydb.shared.dto.SerializableVoid;
import com.google.appengine.api.datastore.KeyFactory;
import com.google.appengine.repackaged.com.google.common.base.Function;
import com.google.appengine.repackaged.com.google.common.collect.Lists;

public class GetLightEmployeeListHandler implements
		ActionHandler<SerializableVoid, ArrayList<LightEmployee>> {

	@SuppressWarnings("unchecked")
	@Override
	public ArrayList<LightEmployee> execute(final SerializableVoid _) {
		final PersistenceManager pm = PMF.get();

		try {
			final javax.jdo.Query query = pm.newQuery(Employee.class);
			query.setOrdering("name asc");

			return new ArrayList<LightEmployee>(Lists.transform(
					(List<Employee>) query.execute(),
					new Function<Employee, LightEmployee>() {

						@Override
						public LightEmployee apply(final Employee employee) {
							return new LightEmployee(KeyFactory
									.keyToString(employee.getKey()), employee
									.getName(), employee.getAppointment(),
									employee.getSalary());
						}
					}));
		} finally {
			pm.close();
		}
	}
}
