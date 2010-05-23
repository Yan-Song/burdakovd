package com.appspot.milkydb.server;

import javax.persistence.Id;

import com.appspot.milkydb.server.models.FinalProductClass;
import com.appspot.milkydb.server.models.RawMaterialClass;
import com.appspot.milkydb.shared.models.Appointment;
import com.appspot.milkydb.shared.models.Employee;
import com.googlecode.objectify.Key;
import com.googlecode.objectify.ObjectifyService;
import com.googlecode.objectify.helper.DAOBase;

public class DAO extends DAOBase {
	static class Dummy {
		@Id
		String key;
	}

	static {
		registerModels();
	}

	/*
	 * по этому ключу ничего не будет храниться, он нужен только чтоб
	 * использовать его в качестве родительского
	 */
	public static Key<?> rootKey = new Key<Dummy>(Dummy.class, "root");

	private static void registerModels() {
		ObjectifyService.register(Dummy.class);
		ObjectifyService.register(Appointment.class);
		ObjectifyService.register(Employee.class);
		ObjectifyService.register(RawMaterialClass.class);
		ObjectifyService.register(FinalProductClass.class);
	}

}
