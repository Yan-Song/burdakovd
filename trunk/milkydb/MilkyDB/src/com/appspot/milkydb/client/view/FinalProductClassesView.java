package com.appspot.milkydb.client.view;

import com.appspot.milkydb.client.presenter.AbstractEntitiesTablePresenter.Display;
import com.appspot.milkydb.shared.models.FinalProductClass;

public class FinalProductClassesView extends
		AbstractProductClassesView<FinalProductClass> implements
		Display<FinalProductClass> {

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * com.appspot.milkydb.client.view.AbstractProductClassesView#getContractsCount
	 * (com.appspot.milkydb.shared.models.BaseProductClass)
	 */
	@Override
	protected int getContractsCount(final FinalProductClass entity) {
		return entity.getContracts().size();
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @seecom.appspot.milkydb.client.view.AbstractProductClassesView#
	 * getContractsCountColumnName()
	 */
	@Override
	protected String getContractsCountColumnName() {
		return "Количество контрактов на продажу";
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * com.appspot.milkydb.client.view.AbstractProductClassesView#getInStorageCount
	 * (com.appspot.milkydb.shared.models.BaseProductClass)
	 */
	@Override
	protected int getInStorageCount(final FinalProductClass entity) {
		return entity.getInStorage().size();
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @seecom.appspot.milkydb.client.view.AbstractProductClassesView#
	 * getInStorageCountColumnName()
	 */
	@Override
	protected String getInStorageCountColumnName() {
		return "Количество партий на складе";
	}

	@Override
	protected String getTableTitle() {
		return "Классы готовой продукции";
	}

}
