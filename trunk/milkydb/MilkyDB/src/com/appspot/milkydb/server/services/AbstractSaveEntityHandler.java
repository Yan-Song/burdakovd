package com.appspot.milkydb.server.services;

import javax.jdo.PersistenceManager;
import javax.jdo.Transaction;

import com.appspot.milkydb.client.validation.ValidationException;
import com.appspot.milkydb.server.PMF;
import com.appspot.milkydb.shared.dto.HasKey;
import com.appspot.milkydb.shared.dto.Validatable;
import com.google.appengine.api.datastore.Key;
import com.google.appengine.api.datastore.KeyFactory;

public abstract class AbstractSaveEntityHandler<Model extends HasKey<Key>, Dto extends Validatable & HasKey<String>>
		implements ActionHandler<Dto, String> {

	private final Class<Model> modelClass;

	public AbstractSaveEntityHandler(final Class<Model> modelClass) {
		this.modelClass = modelClass;
	}

	@Override
	public String execute(final Dto dto) throws ValidationException {

		dto.validate();

		final PersistenceManager pm = PMF.get();

		try {
			return doSave(pm, dto);
		} finally {
			pm.close();
		}
	}

	private String doSave(final PersistenceManager pm, final Dto dto) {
		final boolean newModelInstance = dto.getKey() == null;

		final Transaction t = pm.currentTransaction();
		try {
			t.begin();

			final Model model = newModelInstance ? modelClass.newInstance()
					: pm.getObjectById(modelClass, KeyFactory
							.stringToKey(dto.getKey()));

			setData(model, dto);

			pm.makePersistent(model);

			t.commit();

			return KeyFactory.keyToString(model.getKey());

		} catch (final InstantiationException e) {
			throw new RuntimeException(e);
		} catch (final IllegalAccessException e) {
			throw new RuntimeException(e);
		} finally {
			if (t.isActive()) {
				t.rollback();
			}
		}
	}

	protected abstract void setData(Model model, Dto dto);
}
