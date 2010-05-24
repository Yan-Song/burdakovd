package com.appspot.milkydb.server.services;

import com.appspot.milkydb.server.DAO;
import com.appspot.milkydb.shared.Model;
import com.appspot.milkydb.shared.dto.Dto;
import com.appspot.milkydb.shared.dto.DtoList;
import com.appspot.milkydb.shared.dto.RpcVoid;
import com.google.appengine.repackaged.com.google.common.base.Function;
import com.google.appengine.repackaged.com.google.common.collect.Iterables;
import com.googlecode.objectify.Query;

public abstract class AbstractGetAllEntitiesHandler<M extends Model, LightDto extends Dto>
		implements ActionHandler<RpcVoid, DtoList<LightDto>> {

	private final Class<M> modelClass;

	public AbstractGetAllEntitiesHandler(final Class<M> modelClass) {
		this.modelClass = modelClass;
	}

	public DtoList<LightDto> execute(final RpcVoid _) {

		final DAO dao = new DAO();

		final Query<M> query = dao.ofy().query(modelClass).order(getOrdering())
				.ancestor(DAO.rootKey);

		final DtoList<LightDto> dtoList = new DtoList<LightDto>(Iterables
				.transform(query, new Function<M, LightDto>() {
					@Override
					public LightDto apply(final M model) {
						return makeLightDto(model);
					}
				}));

		return dtoList;
	}

	/*
	 * здесь наследующие классы должны определить порядок сортировки
	 */
	protected abstract String getOrdering();

	/*
	 * Здесь наследующие классы должны создать light data transfer object из
	 * модели
	 */
	protected abstract LightDto makeLightDto(M model);
}
