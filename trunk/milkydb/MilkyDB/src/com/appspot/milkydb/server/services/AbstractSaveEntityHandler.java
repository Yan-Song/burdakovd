package com.appspot.milkydb.server.services;

import com.appspot.milkydb.client.validation.ValidationError;
import com.appspot.milkydb.server.DAO;
import com.appspot.milkydb.shared.HasKey;
import com.appspot.milkydb.shared.HasParent;
import com.appspot.milkydb.shared.Model;
import com.appspot.milkydb.shared.Validatable;
import com.appspot.milkydb.shared.dto.Dto;
import com.appspot.milkydb.shared.dto.SingleKey;
import com.googlecode.objectify.Key;
import com.googlecode.objectify.Objectify;

public abstract class AbstractSaveEntityHandler<M extends HasKey<Long> & Model & HasParent, FullDto extends Validatable & HasKey<Long> & Dto>
		implements ActionHandler<FullDto, SingleKey> {

	private final Class<M> modelClass;

	public AbstractSaveEntityHandler(final Class<M> modelClass) {
		this.modelClass = modelClass;
	}

	protected M doSave(final FullDto dto, final Objectify ofy)
			throws ValidationError {

		try {
			final boolean newModelInstance = dto.getKey() == null;

			M model;
			if (newModelInstance) {
				model = modelClass.newInstance();
				model.setParent(DAO.rootKey);
			} else {
				model = ofy.get(new Key<M>(DAO.rootKey, modelClass, dto
						.getKey()));
			}

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
			final M savedModel = doSave(dto, ofy);

			ofy.getTxn().commit();

			return new SingleKey(savedModel.getKey());

		} finally {
			if (ofy.getTxn().isActive()) {
				ofy.getTxn().rollback();
			}
		}
	}

	/**
	 * Скопировать поля полученного dto в поля модели, кроме ключа. Ключ
	 * копировать не надо, так как он будет сгенерирован или получен из
	 * хранилища. Также не следует заполнять поле owner.
	 * 
	 * @param model
	 *            - куда нужно сохранить
	 * @param dto
	 *            - полученные данные
	 */
	protected abstract void setData(M model, FullDto dto)
			throws ValidationError;
}
