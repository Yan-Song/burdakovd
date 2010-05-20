package com.appspot.milkydb.client.view;

import java.util.ArrayList;
import java.util.List;

import com.appspot.milkydb.client.presenter.EmployeePresenter;
import com.appspot.milkydb.shared.dto.LightEmployee;
import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.event.dom.client.HasClickHandlers;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.CheckBox;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.Grid;
import com.google.gwt.user.client.ui.HorizontalPanel;
import com.google.gwt.user.client.ui.VerticalPanel;
import com.google.gwt.user.client.ui.Widget;
import com.google.gwt.user.client.ui.HTMLTable.Cell;

public class EmployeeView extends Composite implements
		EmployeePresenter.Display {

	private static final String CHECKBOX_COLUMN_WIDTH = "23px";
	private static final String TableTitle = "Список служащих";
	private static final String[] TableHeaders = { "", "ФИО", "Должность",
			"Оклад" };
	private static final int TableColumns = TableHeaders.length;

	private final Grid listing = new Grid(1, TableColumns) {
		{
			addStyleName("listing");
			setTitle(TableTitle);
			getRowFormatter().addStyleName(0, "header");
			for (int i = 0; i < TableHeaders.length; ++i) {
				setText(0, i, TableHeaders[i]);
			}
			getCellFormatter().setWidth(0, 0, CHECKBOX_COLUMN_WIDTH);
		}
	};

	private final Button addButton = new Button("Добавить");
	private final Button deleteButton = new Button("Удалить отмеченные");
	private final Button refreshButton = new Button("Обновить список");

	private final HorizontalPanel menu = new HorizontalPanel() {
		{
			addStyleName("buttons");
			add(addButton);
			add(deleteButton);
			add(refreshButton);
		}
	};

	private final VerticalPanel content = new VerticalPanel() {
		{
			add(menu);
			add(listing);
			setWidth("100%");
		}
	};

	private List<CheckBox> checkboxes;

	public EmployeeView() {
		initWidget(content);
	}

	@Override
	public Widget asWidget() {
		return this;
	}

	private CheckBox createCheckbox() {
		final CheckBox checkBox = new CheckBox();
		checkBox.addClickHandler(new ClickHandler() {
			@Override
			public void onClick(final ClickEvent event) {
				event.stopPropagation();
			}
		});
		return checkBox;
	}

	@Override
	public HasClickHandlers getAddButton() {
		return addButton;
	}

	@Override
	public HasClickHandlers getDeleteButton() {
		return deleteButton;
	}

	@Override
	public HasClickHandlers getEntitiesTable() {
		return listing;
	}

	@Override
	public HasClickHandlers getRefreshButton() {
		return refreshButton;
	}

	@Override
	public int getRowForEvent(final ClickEvent event) {
		final Cell cell = listing.getCellForEvent(event);

		return cell == null ? -1 : cell.getRowIndex() - 1;
	}

	@Override
	public List<Integer> getSelectedRows() {
		final ArrayList<Integer> ans = new ArrayList<Integer>();
		for (int i = 0; i < checkboxes.size(); ++i) {
			if (checkboxes.get(i).getValue()) {
				ans.add(i);
			}
		}

		return ans;
	}

	@Override
	public void setData(final List<LightEmployee> employees) {
		listing.resize(employees.size() + 1, TableColumns);
		checkboxes = new ArrayList<CheckBox>();

		for (int i = 0; i < employees.size(); ++i) {
			final CheckBox checkBox = createCheckbox();
			checkboxes.add(checkBox);
			listing.setWidget(i + 1, 0, checkBox);
			listing.getCellFormatter()
					.setWidth(i + 1, 0, CHECKBOX_COLUMN_WIDTH);
			listing.setText(i + 1, 1, employees.get(i).name);
			listing.setText(i + 1, 2, employees.get(i).post);
			listing.setText(i + 1, 3, employees.get(i).salary.toString()
					+ " руб.");
		}
	}
}
