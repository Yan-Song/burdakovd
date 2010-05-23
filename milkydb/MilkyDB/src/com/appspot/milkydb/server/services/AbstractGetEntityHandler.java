package com.appspot.milkydb.server.services;

import com.appspot.milkydb.server.DAO;
import com.appspot.milkydb.shared.Model;
import com.appspot.milkydb.shared.dto.Dto;
import com.appspot.milkydb.shared.dto.SingleKey;
import com.googlecode.objectify.Key;

public abstract class AbstractGetEntityHandler<M extends Model, FullDto extends Dto>
		implements ActionHandler<SingleKey, FullDto> {

	private final Class<M> modelClass;

	public AbstractGetEntityHandler(final Class<M> modelClass) {
		this.modelClass = modelClass;
	}

	@Override
	public FullDto execute(final SingleKey single) {

		final DAO dao = new DAO();

		final Key<M> key = new Key<M>(DAO.rootKey, modelClass, single
				.getValue());
		return makeDto(dao.ofy().get(key));
	}

	/*
	 * наследующие классы должны создавать здесь DTO из модели
	 */
	protected abstract FullDto makeDto(M model);
}
