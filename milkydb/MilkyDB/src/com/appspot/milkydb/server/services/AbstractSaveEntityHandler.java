package com.appspot.milkydb.server.services;

import com.appspot.milkydb.client.validation.ValidationError;
import com.appspot.milkydb.server.DAO;
import com.appspot.milkydb.shared.HasKey;
import com.appspot.milkydb.shared.Validatable;
import com.appspot.milkydb.shared.dto.Dto;
import com.appspot.milkydb.shared.dto.SingleKey;
import com.googlecode.objectify.Key;
import com.googlecode.objectify.Objectify;

public abstract class AbstractSaveEntityHandler<M extends HasKey<Long>, FullDto extends Validatable & HasKey<Long> & Dto>
		implements ActionHandler<FullDto, SingleKey> {

	private final Class<M> modelClass;

	public AbstractSaveEntityHandler(final Class<M> modelClass) {
		this.modelClass = modelClass;
	}

	protected M doSave(final FullDto dto, final Objectify ofy) {

		try {
			final boolean newModelInstance = dto.getKey() == null;

			final M model = newModelInstance ? modelClass.newInstance() : ofy
					.get(new Key<M>(DAO.rootKey, modelClass, dto.getKey()));

			setData(model, dto);

			ofy.put(model);
			return model;
		} catch (final InstantiationException e) {
			throw new RuntimeException(e);
		} catch (final IllegalAccessException e) {
			throw new RuntimeException(e);
		}
	}

	@Override
	public SingleKey execute(final FullDto dto) throws ValidationError {

		dto.validate();

		final DAO dao = new DAO();

		final Objectify ofy = dao.fact().beginTransaction();

		try {
			final M model = doSave(dto, ofy);

			ofy.getTxn().commit();

			return new SingleKey(model.getKey());

		} finally {
			if (ofy.getTxn().isActive()) {
				ofy.getTxn().rollback();
			}
		}
	}

	protected abstract void setData(M model, FullDto dto);
}
