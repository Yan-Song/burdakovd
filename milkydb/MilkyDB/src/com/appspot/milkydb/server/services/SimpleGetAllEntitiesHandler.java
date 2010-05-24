package com.appspot.milkydb.server.services;

import com.appspot.milkydb.shared.Model;
import com.appspot.milkydb.shared.dto.Dto;
import com.appspot.milkydb.shared.dto.DtoList;
import com.appspot.milkydb.shared.dto.RpcVoid;

public class SimpleGetAllEntitiesHandler<M extends Model & Dto> extends
		AbstractGetAllEntitiesHandler<M, M> implements
		ActionHandler<RpcVoid, DtoList<M>> {

	private final String orderExpression;

	/**
	 * @param modelClass
	 *            - класс модели, список экземпляров которой нужно получить из
	 *            хранилища
	 * @param orderExpression
	 *            - поле сортировки
	 */
	public SimpleGetAllEntitiesHandler(final Class<M> modelClass,
			final String orderExpression) {
		super(modelClass);
		this.orderExpression = orderExpression;
	}

	@Override
	protected String getOrdering() {
		return orderExpression;
	}

	@Override
	protected M makeLightDto(final M model) {
		return model;
	}
}
