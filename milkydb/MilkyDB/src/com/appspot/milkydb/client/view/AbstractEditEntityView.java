package com.appspot.milkydb.client.view;

import java.util.HashMap;
import java.util.Map;

import com.appspot.milkydb.client.presenter.AbstractEditEntityPresenter;
import com.appspot.milkydb.client.ui.FormField;
import com.appspot.milkydb.client.validation.ValidationError;
import com.appspot.milkydb.shared.Validatable;
import com.appspot.milkydb.shared.Validatable.Fields;
import com.google.gwt.event.dom.client.HasClickHandlers;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.FlexTable;
import com.google.gwt.user.client.ui.HorizontalPanel;
import com.google.gwt.user.client.ui.Widget;

public abstract class AbstractEditEntityView extends Composite implements
		AbstractEditEntityPresenter.Display {

	private static final String validationFailedClass = "validation-failed";

	protected final Button submitButton = new Button("Сохранить");
	protected final Button cancelButton = new Button("Отмена");

	private final HorizontalPanel buttons = new HorizontalPanel() {
		{
			addStyleName("buttons");
			add(submitButton);
			add(cancelButton);
		}
	};

	public AbstractEditEntityView() {
	}

	@Override
	public Widget asWidget() {
		return this;
	}

	@Override
	public void clearErrors() {
		for (final FormField<?> w : getFieldsMap().values()) {
			w.getErrorLabel().setVisible(false);
			w.getField().removeStyleName(validationFailedClass);
		}
	}

	@Override
	public HasClickHandlers getCancelButton() {
		return cancelButton;
	}

	protected abstract HashMap<Enum<? extends Fields>, FormField<?>> getFieldsMap();

	@Override
	public HasClickHandlers getSubmitButton() {
		return submitButton;
	}

	protected void initForm(final FormField<?>[] fields) {
		initWidget(new FlexTable() {
			{
				addStyleName("form");

				for (int i = 0; i < fields.length; ++i) {
					setWidget(i, 0, fields[i].getLabel());
					setWidget(i, 1, fields[i].getField());
					setWidget(i, 2, fields[i].getErrorLabel());
				}

				setWidget(fields.length, 1, buttons);
			}
		});
	}

	@Override
	public void showValidationError(final ValidationError error) {
		for (final Map.Entry<Enum<? extends Validatable.Fields>, String> entry : error
				.getErrors().entrySet()) {
			final FormField<?> field = getFieldsMap().get(entry.getKey());
			field.getErrorLabel().setText(entry.getValue());
			field.getErrorLabel().setVisible(true);
			field.getField().addStyleName(validationFailedClass);
		}
	}
}
