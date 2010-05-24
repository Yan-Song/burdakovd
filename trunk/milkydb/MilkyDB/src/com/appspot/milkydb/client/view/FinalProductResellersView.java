/**
 * 
 */
package com.appspot.milkydb.client.view;

import com.appspot.milkydb.shared.models.FinalProductReseller;

/**
 * @author burdakovd
 * 
 */
public class FinalProductResellersView extends
		AbstractPartnersView<FinalProductReseller> {

	/**
	 * 
	 */
	public FinalProductResellersView() {
		super();
	}

	@Override
	protected int getContractCount(final FinalProductReseller entity) {
		return entity.getDemands().size();
	}

	@Override
	protected String getContractCountColumnName() {
		return "Количество договоров на продажу";
	}

	@Override
	protected String getTableTitle() {
		return "Список магазинов, покупающих у нас конечный продукт";
	}

}
