package com.appspot.milkydb.server.services;

import java.util.ArrayList;
import java.util.List;

import javax.jdo.PersistenceManager;

import com.appspot.milkydb.client.services.MilkyService;
import com.appspot.milkydb.server.PMF;
import com.appspot.milkydb.server.Models.Employee;
import com.appspot.milkydb.shared.LightEmployeeDetails;
import com.google.appengine.repackaged.com.google.common.base.Function;
import com.google.appengine.repackaged.com.google.common.collect.Lists;
import com.google.gwt.user.server.rpc.RemoteServiceServlet;

@SuppressWarnings("serial")
public class MilkyServiceImpl extends RemoteServiceServlet implements
		MilkyService {

	@SuppressWarnings("unchecked")
	@Override
	public ArrayList<LightEmployeeDetails> getEmployeeList() {
		final PersistenceManager pm = PMF.get();
		final javax.jdo.Query query = pm.newQuery(Employee.class);
		query.setOrdering("name asc");

		return new ArrayList<LightEmployeeDetails>(Lists.transform(
				(List<Employee>) query.execute(),
				new Function<Employee, LightEmployeeDetails>() {
					@Override
					public LightEmployeeDetails apply(final Employee employee) {
						return new LightEmployeeDetails(employee.getName(),
								employee.getAppointment().getName(), employee
										.getSalary());
					}
				}));
	}
}
