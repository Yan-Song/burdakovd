package com.appspot.milkydb.client.view;

import com.appspot.milkydb.shared.dto.LightProductClass;
import com.google.gwt.user.client.ui.Grid;

public abstract class AbstractProductClassView extends
		AbstractEntitiesTableView<LightProductClass> {

	@Override
	protected void displayEntity(final LightProductClass entity,
			final Grid listing, final int row, final int firstColumn) {
		listing.setText(row, firstColumn, entity.getName());
		listing.setText(row, firstColumn + 1, entity.getFatness().toString()
				+ "%");
		listing.setText(row, firstColumn + 2, entity.getCalorificValue()
				.toString()
				+ " ккал");
		listing.setText(row, firstColumn + 3, entity.getStorageLife()
				.toString());
	}

	@Override
	protected int getTableColumnsCount() {
		return 4;
	}

	@Override
	protected String[] getTableHeaders() {
		return new String[] { "Название", "Жирность",
				"Энергетическая ценность", "Срок хранения" };
	}
}
