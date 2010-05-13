package com.appspot.milkydb.client.view;

import com.appspot.milkydb.client.presenter.EditEmployeePresenter;
import com.appspot.milkydb.client.ui.FreeListBox;
import com.appspot.milkydb.client.ui.Labeled;
import com.google.gwt.event.dom.client.HasClickHandlers;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.FlexTable;
import com.google.gwt.user.client.ui.HasValue;
import com.google.gwt.user.client.ui.HorizontalPanel;
import com.google.gwt.user.client.ui.TextBox;
import com.google.gwt.user.client.ui.Widget;

public class EditEmployeeView extends Composite implements
		EditEmployeePresenter.Display {

	private final Labeled<TextBox> name = new Labeled<TextBox>("ФИО",
			new TextBox());

	private final Labeled<FreeListBox> post = new Labeled<FreeListBox>(
			"Должность", new FreeListBox());

	private final Labeled<TextBox> salary = new Labeled<TextBox>("Оклад",
			new TextBox());

	private final Button submitButton = new Button("Сохранить");

	private final Button cancelButton = new Button("Отмена");

	private final HorizontalPanel buttons = new HorizontalPanel() {
		{
			addStyleName("buttons");
			add(submitButton);
			add(cancelButton);
		}
	};

	private final FlexTable form = new FlexTable() {
		{
			addStyleName("form");
			setWidget(0, 0, name.getLabel());
			setWidget(0, 1, name.getField());
			setWidget(1, 0, post.getLabel());
			setWidget(1, 1, post.getField());
			setWidget(2, 0, salary.getLabel());
			setWidget(2, 1, salary.getField());
			setWidget(3, 1, buttons);
		}
	};

	public EditEmployeeView() {
		initWidget(form);
	}

	@Override
	public Widget asWidget() {
		return this;
	}

	@Override
	public HasClickHandlers getCancelButton() {
		return cancelButton;
	}

	@Override
	public HasValue<String> getName() {
		return name.getField();
	}

	@Override
	public HasValue<String> getPost() {
		return post.getField();
	}

	@Override
	public HasValue<String> getSalary() {
		return salary.getField();
	}

	@Override
	public HasClickHandlers getSubmitButton() {
		return submitButton;
	}

}
