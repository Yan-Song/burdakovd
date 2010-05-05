package com.appspot.milkydb.client.view;

import java.util.List;

import com.appspot.milkydb.client.presenter.EmployeePresenter.Display;
import com.appspot.milkydb.shared.LightEmployeeDetails;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.Grid;
import com.google.gwt.user.client.ui.Widget;

public class EmployeeView extends Composite implements Display {

	private final int Width = 3;
	private final String Title = "Список служащих";
	private final String[] headers = { "ФИО", "Должность", "Оклад" };

	private final Grid table = new Grid(1, Width) {
		{
			addStyleName("listing");
			setTitle(Title);
			getRowFormatter().addStyleName(0, "header");
			for (int i = 0; i < headers.length; ++i) {
				setText(0, i, headers[i]);
			}
		}
	};

	public EmployeeView() {
		initWidget(table);
	}

	@Override
	public Widget asWidget() {
		return this;
	}

	@Override
	public void setData(final List<LightEmployeeDetails> employees) {
		table.resize(employees.size() + 1, Width);
		for (int i = 0; i < employees.size(); ++i) {
			table.setText(i + 1, 0, employees.get(i).name);
			table.setText(i + 1, 1, employees.get(i).post);
			table.setText(i + 1, 2, ((Double) employees.get(i).salary)
					.toString());
		}
	}
}
