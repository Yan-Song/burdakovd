package com.appspot.milkydb.client.view;

import java.util.List;

import com.appspot.milkydb.client.presenter.EmployeePresenter.Display;
import com.appspot.milkydb.shared.LightEmployeeDetails;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.Grid;
import com.google.gwt.user.client.ui.Widget;

public class EmployeeView extends Composite implements Display {

	private final Grid table = new Grid();

	public EmployeeView() {
		initWidget(table);
	}

	@Override
	public Widget asWidget() {
		return this;
	}

	@Override
	public void setData(final List<LightEmployeeDetails> employees) {
		table.resize(employees.size(), 3);
		for (int i = 0; i < employees.size(); ++i) {
			table.setText(i, 0, employees.get(i).name);
			table.setText(i, 1, employees.get(i).post);
			table.setText(i, 2, ((Double) employees.get(i).salary).toString());
		}
	}
}
