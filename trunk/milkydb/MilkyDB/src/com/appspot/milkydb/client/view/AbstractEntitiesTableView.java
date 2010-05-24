package com.appspot.milkydb.client.view;

import java.util.ArrayList;
import java.util.List;

import com.appspot.milkydb.client.presenter.AbstractEntitiesTablePresenter;
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

public abstract class AbstractEntitiesTableView<Entity> extends Composite
		implements AbstractEntitiesTablePresenter.Display<Entity> {

	private static final String checkBoxColumnWidth = "23px";
	private static final int headerRow = 0;

	private final Grid listing = createListing();

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

	public AbstractEntitiesTableView() {
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

	private void createCheckboxes(final int count) {
		checkboxes = new ArrayList<CheckBox>();

		for (int i = 0; i < count; ++i) {
			final CheckBox checkBox = createCheckbox();
			checkboxes.add(checkBox);
			listing.setWidget(i + 1, 0, checkBox);
			listing.getCellFormatter().setWidth(i + 1, 0, checkBoxColumnWidth);
		}
	}

	private Grid createListing() {
		return new Grid(1, getTableColumnsCount() + 1) {
			{
				addStyleName("listing");
				setTitle(getTableTitle());
				getRowFormatter().addStyleName(0, "header");

				final String[] headers = getTableHeaders();
				for (int i = 0; i < getTableColumnsCount(); ++i) {
					setText(headerRow, i + 1, headers[i]);
				}

				getCellFormatter().setWidth(0, 0, checkBoxColumnWidth);
			}
		};
	}

	protected abstract void displayEntity(Entity entity, final Grid listing,
			final int row, final int firstColumn);

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

	protected abstract int getTableColumnsCount();

	protected abstract String[] getTableHeaders();

	protected abstract String getTableTitle();

	private void resizeListing(final int count) {
		listing.resize(count + 1, getTableColumnsCount() + 1);
	}

	@Override
	public void setData(final List<? extends Entity> entities) {
		resizeListing(entities.size());
		createCheckboxes(entities.size());
		for (int i = 0; i < entities.size(); ++i) {
			displayEntity(entities.get(i), listing, i + 1, 1);
		}
	}
}
