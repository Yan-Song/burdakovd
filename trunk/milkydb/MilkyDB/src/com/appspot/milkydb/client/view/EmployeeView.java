package com.appspot.milkydb.client.view;

import com.appspot.milkydb.client.presenter.EmployeePresenter;
import com.appspot.milkydb.shared.dto.LightEmployee;
import com.google.gwt.user.client.ui.Grid;

public class EmployeeView extends AbstractEntitiesTableView<LightEmployee>
		implements EmployeePresenter.Display {

	@Override
	protected void displayEntity(final LightEmployee employee,
			final Grid listing, final int row, final int firstColumn) {
		listing.setText(row, firstColumn, employee.name);
		listing.setText(row, firstColumn + 1, employee.post);
		listing.setText(row, firstColumn + 2, employee.salary.toString()
				+ " руб.");
	}

	@Override
	protected int getTableColumnsCount() {
		return 3;
	}

	@Override
	protected String[] getTableHeaders() {
		return new String[] { "Ф.И.О.", "Должность", "Оклад" };
	}

	@Override
	protected String getTableTitle() {
		return "Список сотрудников";
	}
}