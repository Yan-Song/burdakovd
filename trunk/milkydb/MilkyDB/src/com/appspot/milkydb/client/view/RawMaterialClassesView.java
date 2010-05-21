package com.appspot.milkydb.client.view;

import com.appspot.milkydb.client.presenter.RawMaterialClassesPresenter;
import com.appspot.milkydb.shared.dto.LightProductClass;
import com.google.gwt.user.client.ui.Grid;

public class RawMaterialClassesView extends
		AbstractEntitiesTableView<LightProductClass> implements
		RawMaterialClassesPresenter.Display {

	@Override
	protected void displayEntity(final LightProductClass entity,
			final Grid listing, final int row, final int firstColumn) {
		listing.setText(row, firstColumn, entity.name);
		listing.setText(row, firstColumn + 1, entity.fatness.toString() + "%");
		listing.setText(row, firstColumn + 2, entity.calorificValue.toString()
				+ " ккал");
		listing.setText(row, firstColumn + 3, entity.storageLife.toString());
	}

	@Override
	protected int getTableColumnsCount() {
		return 4;
	}

	@Override
	protected String[] getTableHeaders() {
		return new String[] { "Название", "Жирность", "Калорийность",
				"Срок хранения" };
	}

	@Override
	protected String getTableTitle() {
		return "Классы сырья";
	}

}
