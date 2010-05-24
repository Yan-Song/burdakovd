/**
 * 
 */
package com.appspot.milkydb.client.view;

import com.appspot.milkydb.shared.models.Partner;
import com.google.gwt.user.client.ui.Grid;

/**
 * @author burdakovd
 * 
 */
public abstract class AbstractPartnersView<FullDto extends Partner> extends
		AbstractEntitiesTableView<FullDto> {

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * com.appspot.milkydb.client.view.AbstractEntitiesTableView#displayEntity
	 * (java.lang.Object, com.google.gwt.user.client.ui.Grid, int, int)
	 */
	@Override
	protected void displayEntity(final FullDto entity, final Grid listing,
			final int row, final int firstColumn) {
		listing.setText(row, firstColumn, entity.getName());
		listing.setText(row, firstColumn + 1, String
				.valueOf(getContractCount(entity)));
	}

	protected abstract int getContractCount(FullDto entity);

	protected abstract String getContractCountColumnName();

	/*
	 * (non-Javadoc)
	 * 
	 * @seecom.appspot.milkydb.client.view.AbstractEntitiesTableView#
	 * getTableColumnsCount()
	 */
	@Override
	protected int getTableColumnsCount() {
		return 2;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * com.appspot.milkydb.client.view.AbstractEntitiesTableView#getTableHeaders
	 * ()
	 */
	@Override
	protected String[] getTableHeaders() {
		return new String[] { "Название", getContractCountColumnName() };
	}
}
