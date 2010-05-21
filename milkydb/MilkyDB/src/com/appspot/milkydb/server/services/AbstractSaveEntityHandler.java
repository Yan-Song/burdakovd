package com.appspot.milkydb.server.services;

import javax.jdo.PersistenceManager;
import javax.jdo.Transaction;

import com.appspot.milkydb.client.validation.ValidationError;
import com.appspot.milkydb.server.PMF;
import com.appspot.milkydb.shared.HasKey;
import com.appspot.milkydb.shared.Validatable;
import com.appspot.milkydb.shared.dto.Dto;
import com.appspot.milkydb.shared.dto.EncodedKey;
import com.google.appengine.api.datastore.Key;
import com.google.appengine.api.datastore.KeyFactory;

public abstract class AbstractSaveEntityHandler<Model extends HasKey<Key>, FullDto extends Validatable & HasKey<EncodedKey> & Dto>
		implements ActionHandler<FullDto, EncodedKey> {

	private final Class<Model> modelClass;

	public AbstractSaveEntityHandler(final Class<Model> modelClass) {
		this.modelClass = modelClass;
	}

	private EncodedKey doSave(final PersistenceManager pm, final FullDto dto) {
		final boolean newModelInstance = dto.getKey() == null;

		final Transaction t = pm.currentTransaction();
		try {
			t.begin();

			final Model model = newModelInstance ? modelClass.newInstance()
					: pm.getObjectById(modelClass, KeyFactory.stringToKey(dto
							.getKey().getValue()));

			setData(model, dto);

			pm.makePersistent(model);

			t.commit();

			return new EncodedKey(KeyFactory.keyToString(model.getKey()));

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

	@Override
	public EncodedKey execute(final FullDto dto) throws ValidationError {

		dto.validate();

		final PersistenceManager pm = PMF.get();

		try {
			return doSave(pm, dto);
		} finally {
			pm.close();
		}
	}

	protected abstract void setData(Model model, FullDto dto);
}
