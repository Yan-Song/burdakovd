package com.appspot.milkydb.server;

import com.appspot.milkydb.server.models.FinalProductClass;
import com.appspot.milkydb.server.models.RawMaterialClass;
import com.appspot.milkydb.shared.models.Appointment;
import com.appspot.milkydb.shared.models.Employee;
import com.googlecode.objectify.Key;
import com.googlecode.objectify.ObjectifyService;
import com.googlecode.objectify.helper.DAOBase;

public class DAO extends DAOBase {
	static {
		ObjectifyService.register(Appointment.class);
		ObjectifyService.register(Employee.class);
		ObjectifyService.register(RawMaterialClass.class);
		ObjectifyService.register(FinalProductClass.class);
	}

	/*
	 * по этому ключу ничего не будет храниться, он нужен только чтоб
	 * использовать его в качестве родительского
	 */
	public static Key<?> rootKey = new Key<DAO>(DAO.class, "root");

}
