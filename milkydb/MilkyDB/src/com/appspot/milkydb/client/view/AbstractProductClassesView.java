package com.appspot.milkydb.client.view;

import com.appspot.milkydb.shared.models.BaseProductClass;
import com.google.gwt.user.client.ui.Grid;

public abstract class AbstractProductClassesView<M extends BaseProductClass>
		extends AbstractEntitiesTableView<M> {

	@Override
	protected void displayEntity(final M entity, final Grid listing,
			final int row, final int firstColumn) {
		listing.setText(row, firstColumn, entity.getName());
		listing.setText(row, firstColumn + 1, entity.getFatness().toString()
				+ "%");
		listing.setText(row, firstColumn + 2, entity.getCalorificValue()
				.toString()
				+ " ккал");
		listing.setText(row, firstColumn + 3, entity.getStorageLife()
				.toString());

		listing.setText(row, firstColumn + 4, String
				.valueOf(getContractsCount(entity)));

		listing.setText(row, firstColumn + 5, String
				.valueOf(getInStorageCount(entity)));
	}

	protected abstract int getContractsCount(M entity);

	protected abstract String getContractsCountColumnName();

	protected abstract int getInStorageCount(M entity);

	protected abstract String getInStorageCountColumnName();

	@Override
	protected int getTableColumnsCount() {
		return 6;
	}

	@Override
	protected String[] getTableHeaders() {
		return new String[] { "Название", "Жирность",
				"Энергетическая ценность", "Срок хранения",
				getContractsCountColumnName(), getInStorageCountColumnName() };
	}
}
