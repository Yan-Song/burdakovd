package com.appspot.milkydb.server;

import javax.persistence.Id;

import com.appspot.milkydb.shared.models.Appointment;
import com.appspot.milkydb.shared.models.Employee;
import com.appspot.milkydb.shared.models.Ferment;
import com.appspot.milkydb.shared.models.FinalProductClass;
import com.appspot.milkydb.shared.models.MicroElement;
import com.appspot.milkydb.shared.models.RawMaterialClass;
import com.appspot.milkydb.shared.models.SingleStringModel;
import com.googlecode.objectify.Key;
import com.googlecode.objectify.NotFoundException;
import com.googlecode.objectify.Objectify;
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

	public static <M extends SingleStringModel> M getOrCreate(
			final Class<M> modelClass, final Objectify ofy, final String name) {

		final Key<M> key = new Key<M>(DAO.rootKey, modelClass, name);

		M model;

		try {
			model = ofy.get(key);
		} catch (final NotFoundException e) {

			try {
				model = modelClass.newInstance();
			} catch (final InstantiationException e1) {
				throw new RuntimeException(e1);
			} catch (final IllegalAccessException e1) {
				throw new RuntimeException(e1);
			}

			model.setOwner(DAO.rootKey);
			model.setName(name);
			ofy.put(model);
		}

		return model;
	}

	private static void registerModels() {
		ObjectifyService.register(Dummy.class);
		ObjectifyService.register(Appointment.class);
		ObjectifyService.register(Employee.class);
		ObjectifyService.register(RawMaterialClass.class);
		ObjectifyService.register(FinalProductClass.class);
		ObjectifyService.register(Ferment.class);
		ObjectifyService.register(MicroElement.class);
	}

}
