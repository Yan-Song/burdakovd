package com.appspot.milkydb.server.services;

import java.util.List;

import javax.jdo.PersistenceManager;

import com.appspot.milkydb.server.PMF;
import com.appspot.milkydb.shared.dto.Dto;
import com.appspot.milkydb.shared.dto.DtoList;
import com.appspot.milkydb.shared.dto.RpcVoid;
import com.google.appengine.repackaged.com.google.common.base.Function;
import com.google.appengine.repackaged.com.google.common.collect.Lists;

public abstract class AbstractGetEntitiesHandler<Model, LightDto extends Dto>
		implements ActionHandler<RpcVoid, DtoList<LightDto>> {

	private final Class<Model> modelClass;

	public AbstractGetEntitiesHandler(final Class<Model> modelClass) {
		this.modelClass = modelClass;
	}

	@SuppressWarnings("unchecked")
	private DtoList<LightDto> doGet(final PersistenceManager pm) {
		final javax.jdo.Query query = pm.newQuery(modelClass);
		setOrdering(query);

		return new DtoList<LightDto>(Lists.transform((List<Model>) query
				.execute(), new Function<Model, LightDto>() {
			@Override
			public LightDto apply(final Model model) {
				return makeLightDto(model);
			}
		}));
	}

	public DtoList<LightDto> execute(final RpcVoid _) {
		final PersistenceManager pm = PMF.get();

		try {
			return doGet(pm);
		} finally {
			pm.close();
		}
	}

	/*
	 * Здесь наследующие классы должны создать light data transfer object из
	 * модели
	 */
	protected abstract LightDto makeLightDto(Model model);

	/*
	 * здесь наследующие классы должны определить порядок сортировки
	 */
	protected abstract void setOrdering(final javax.jdo.Query query);
}
