package com.appspot.milkydb.client.view;

import java.util.List;

import com.appspot.milkydb.client.presenter.EmployeePresenter;
import com.appspot.milkydb.shared.dto.LightEmployee;
import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.HasClickHandlers;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.Grid;
import com.google.gwt.user.client.ui.HorizontalPanel;
import com.google.gwt.user.client.ui.VerticalPanel;
import com.google.gwt.user.client.ui.Widget;
import com.google.gwt.user.client.ui.HTMLTable.Cell;

public class EmployeeView extends Composite implements
		EmployeePresenter.Display {

	private final int TableColumns = 3;
	private final String TableTitle = "Список служащих";
	private final String[] TableHeaders = { "ФИО", "Должность", "Оклад" };

	private final Grid listing = new Grid(1, TableColumns) {
		{
			addStyleName("listing");
			setTitle(TableTitle);
			getRowFormatter().addStyleName(0, "header");
			for (int i = 0; i < TableHeaders.length; ++i) {
				setText(0, i, TableHeaders[i]);
			}
		}
	};

	private final Button addButton = new Button("Добавить");

	private final HorizontalPanel menu = new HorizontalPanel() {
		{
			addStyleName("buttons");
			add(addButton);
		}
	};

	private final VerticalPanel content = new VerticalPanel() {
		{
			add(menu);
			add(listing);
			setWidth("100%");
		}
	};

	public EmployeeView() {
		initWidget(content);
	}

	@Override
	public Widget asWidget() {
		return this;
	}

	@Override
	public HasClickHandlers getAddButton() {
		return addButton;
	}

	@Override
	public HasClickHandlers getEmployeeTable() {
		return listing;
	}

	@Override
	public int getRowIndexForEvent(final ClickEvent event) {
		final Cell cell = listing.getCellForEvent(event);

		return cell == null ? -1 : cell.getRowIndex() - 1;
	}

	@Override
	public void setData(final List<LightEmployee> employees) {
		listing.resize(employees.size() + 1, TableColumns);
		for (int i = 0; i < employees.size(); ++i) {
			listing.setText(i + 1, 0, employees.get(i).name);
			listing.setText(i + 1, 1, employees.get(i).post);
			listing.setText(i + 1, 2, employees.get(i).salary.toString()
					+ " руб.");
		}
	}
}
