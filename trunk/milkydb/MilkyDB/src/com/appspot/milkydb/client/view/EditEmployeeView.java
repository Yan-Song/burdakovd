package com.appspot.milkydb.client.view;

import java.util.HashMap;
import java.util.Map;

import com.appspot.milkydb.client.presenter.EditEmployeePresenter;
import com.appspot.milkydb.client.ui.FormField;
import com.appspot.milkydb.client.ui.FreeListBox;
import com.appspot.milkydb.client.validation.ValidationError;
import com.appspot.milkydb.shared.dto.FullEmployee;
import com.google.gwt.event.dom.client.HasClickHandlers;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.FlexTable;
import com.google.gwt.user.client.ui.HasValue;
import com.google.gwt.user.client.ui.HorizontalPanel;
import com.google.gwt.user.client.ui.TextArea;
import com.google.gwt.user.client.ui.TextBox;
import com.google.gwt.user.client.ui.Widget;

@SuppressWarnings("serial")
public class EditEmployeeView extends Composite implements
		EditEmployeePresenter.Display {

	private static final String VALIDATION_FAILED_CLASS = "validation-failed";

	private final FormField<TextBox> name = new FormField<TextBox>("ФИО",
			new TextBox());

	private final FormField<FreeListBox> post = new FormField<FreeListBox>(
			"Должность", new FreeListBox());

	private final FormField<TextBox> salary = new FormField<TextBox>(
			"Оклад, руб.", new TextBox());

	private final FormField<TextArea> address = new FormField<TextArea>(
			"Адрес", new TextArea());

	private final FormField<TextBox> phone = new FormField<TextBox>("Телефон",
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

	private final HashMap<String, FormField<?>> fields = new HashMap<String, FormField<?>>() {
		{
			put(FullEmployee.Fields.name, name);
			put(FullEmployee.Fields.post, post);
			put(FullEmployee.Fields.salary, salary);
			put(FullEmployee.Fields.address, address);
			put(FullEmployee.Fields.phoneNumber, phone);
		}
	};

	private final FlexTable form = new FlexTable() {
		{
			addStyleName("form");

			final FormField<?>[] fields = new FormField<?>[] { name, post,
					salary, address, phone };
			for (int i = 0; i < fields.length; ++i) {
				setWidget(i, 0, fields[i].getLabel());
				setWidget(i, 1, fields[i].getField());
				setWidget(i, 2, fields[i].getErrorLabel());
			}

			setWidget(5, 1, buttons);
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
	public void clearErrors() {
		for (final FormField<?> w : fields.values()) {
			w.getErrorLabel().setVisible(false);
			w.getField().removeStyleName(VALIDATION_FAILED_CLASS);
		}
	}

	@Override
	public HasValue<String> getAddress() {
		return address.getField();
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
	public HasValue<String> getPhoneNumber() {
		return phone.getField();
	}

	@Override
	public FreeListBox getPost() {
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

	@Override
	public void showValidationError(final ValidationError exception) {
		for (final Map.Entry<String, String> entry : exception.getErrors()
				.entrySet()) {
			final FormField<?> field = fields.get(entry.getKey());
			field.getErrorLabel().setText(entry.getValue());
			field.getErrorLabel().setVisible(true);
			field.getField().addStyleName(VALIDATION_FAILED_CLASS);
		}
	}
}
