package com.appspot.milkydb.server.services;

import java.util.ArrayList;

import javax.jdo.PersistenceManager;

import com.appspot.milkydb.server.PMF;
import com.appspot.milkydb.server.models.Employee;
import com.appspot.milkydb.shared.dto.SerializableVoid;
import com.google.appengine.api.datastore.KeyFactory;

public class DeleteEmployeeHandler implements
		ActionHandler<ArrayList<String>, SerializableVoid> {

	@Override
	public SerializableVoid execute(final ArrayList<String> keys) {
		final PersistenceManager pm = PMF.get();

		try {

			for (final String key : keys) {
				pm.deletePersistent(pm.getObjectById(Employee.class, KeyFactory
						.stringToKey(key)));
			}

			return null;

		} finally {
			pm.close();
		}
	}
}
