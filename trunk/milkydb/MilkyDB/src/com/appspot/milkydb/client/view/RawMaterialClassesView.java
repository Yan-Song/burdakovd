package com.appspot.milkydb.client.view;

import com.appspot.milkydb.client.presenter.RawMaterialClassesPresenter;
import com.appspot.milkydb.shared.models.RawMaterialClass;

public class RawMaterialClassesView extends
		AbstractProductClassesView<RawMaterialClass> implements
		RawMaterialClassesPresenter.Display {

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * com.appspot.milkydb.client.view.AbstractProductClassesView#getContractsCount
	 * (com.appspot.milkydb.shared.models.BaseProductClass)
	 */
	@Override
	protected int getContractsCount(final RawMaterialClass entity) {
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
		return "Количество контрактов на закупку";
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * com.appspot.milkydb.client.view.AbstractProductClassesView#getInStorageCount
	 * (com.appspot.milkydb.shared.models.BaseProductClass)
	 */
	@Override
	protected int getInStorageCount(final RawMaterialClass entity) {
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
		return "На складе";
	}

	@Override
	protected String getTableTitle() {
		return "Классы сырья";
	}

}
