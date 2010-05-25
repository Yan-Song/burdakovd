package com.appspot.milkydb.server;

import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import javax.persistence.Id;

import com.appspot.milkydb.shared.models.Appointment;
import com.appspot.milkydb.shared.models.Demand;
import com.appspot.milkydb.shared.models.DictionaryModel;
import com.appspot.milkydb.shared.models.Employee;
import com.appspot.milkydb.shared.models.Ferment;
import com.appspot.milkydb.shared.models.FinalProductClass;
import com.appspot.milkydb.shared.models.FinalProductReseller;
import com.appspot.milkydb.shared.models.MicroElement;
import com.appspot.milkydb.shared.models.RawMaterialClass;
import com.appspot.milkydb.shared.models.RawMaterialProvider;
import com.appspot.milkydb.shared.models.Supply;
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

	public static <M extends DictionaryModel> void decrementAndDeleteIfNotUsed(
			final Objectify ofy, final Class<M> modelClass,
			final Map<String, Integer> counts) {
		for (final Map.Entry<String, Integer> entry : counts.entrySet()) {
			decrementAndDeleteIfNotUsed(ofy, modelClass, entry.getKey(), entry
					.getValue());
		}
	}

	public static <M extends DictionaryModel> void decrementAndDeleteIfNotUsed(
			final Objectify ofy, final Class<M> modelClass,
			final Set<String> values) {

		for (final String value : values) {
			decrementAndDeleteIfNotUsed(ofy, modelClass, value);
		}
	}

	public static <M extends DictionaryModel> void decrementAndDeleteIfNotUsed(
			final Objectify ofy, final Class<M> modelClass, final String value) {
		decrementAndDeleteIfNotUsed(ofy, modelClass, value, 1);
	}

	/**
	 * Ожидается, что эта функция будет вызвана внутри транзакции
	 * 
	 * @param <M>
	 * @param modelClass
	 * @param value
	 */
	public static <M extends DictionaryModel> void decrementAndDeleteIfNotUsed(
			final Objectify ofy, final Class<M> modelClass, final String value,
			final int count) {

		if (value == null || "".equals(value)) {
			return;
		}

		final Key<M> key = new Key<M>(DAO.rootKey, modelClass, value);

		try {
			final M model = ofy.get(key);
			model.setLinkCount(model.getLinkCount() - count);
			if (model.getLinkCount().intValue() <= 0) {
				ofy.delete(key);
			} else {
				ofy.put(model);
			}
		} catch (final NotFoundException e) {
			// ok, nothing to do
		}
	}

	public static <M extends DictionaryModel> void incrementAndCreateIfNeeded(
			final Objectify ofy, final Class<M> modelClass,
			final Set<String> values) {
		for (final String value : values) {
			incrementAndCreateIfNeeded(ofy, modelClass, value);
		}
	}

	/**
	 * Ожидается, что эта функция будет вызвана внутри транзакции
	 * 
	 * @param ofy
	 * @param modelClass
	 * @param name
	 * 
	 * @param <M>
	 * @return
	 */
	public static <M extends DictionaryModel> M incrementAndCreateIfNeeded(
			final Objectify ofy, final Class<M> modelClass, final String name) {

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

			model.setParent(DAO.rootKey);
			model.setName(name);
		}

		model.setLinkCount(model.getLinkCount() + 1);
		ofy.put(model);

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
		ObjectifyService.register(RawMaterialProvider.class);
		ObjectifyService.register(FinalProductReseller.class);
		ObjectifyService.register(Supply.class);
		ObjectifyService.register(Demand.class);
	}

	public static <Q extends DictionaryModel> void updateDictionaryFields(
			final Objectify ofy, final Class<Q> modelClass,
			final Set<String> oldValues, final Set<String> newValues) {

		final Set<String> removedFields = new HashSet<String>(oldValues);
		removedFields.removeAll(newValues);
		DAO.decrementAndDeleteIfNotUsed(ofy, modelClass, removedFields);

		final Set<String> addedFields = new HashSet<String>(newValues);
		addedFields.removeAll(oldValues);
		DAO.incrementAndCreateIfNeeded(ofy, modelClass, addedFields);

	}

	public static <Q extends DictionaryModel> void updateDictionaryFields(
			final Objectify ofy, final Class<Q> modelClass,
			final String oldValue, final String newValue) {
		if (!oldValue.equals(newValue)) {
			DAO.decrementAndDeleteIfNotUsed(ofy, modelClass, oldValue);
			DAO.incrementAndCreateIfNeeded(ofy, modelClass, newValue);
		}
	}

}
