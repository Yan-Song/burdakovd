/**
 * 
 */
package com.appspot.milkydb.client.view;

import com.appspot.milkydb.shared.models.RawMaterialProvider;

/**
 * @author burdakovd
 * 
 */
public class RawMaterialProvidersView extends
		AbstractPartnersView<RawMaterialProvider> {

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * com.appspot.milkydb.client.view.AbstractPartnersView#getContractCount
	 * (com.appspot.milkydb.shared.models.Partner)
	 */
	@Override
	protected int getContractCount(final RawMaterialProvider entity) {
		return entity.getSupplies().size();
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @seecom.appspot.milkydb.client.view.AbstractPartnersView#
	 * getContractCountColumnName()
	 */
	@Override
	protected String getContractCountColumnName() {
		return "Количество договоров на поставку";
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * com.appspot.milkydb.client.view.AbstractEntitiesTableView#getTableTitle()
	 */
	@Override
	protected String getTableTitle() {
		return "Список поставщиков сырья";
	}

}
