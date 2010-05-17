package com.appspot.milkydb.client.ui;

import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.HasVerticalAlignment;
import com.google.gwt.user.client.ui.HorizontalPanel;
import com.google.gwt.user.client.ui.Label;
import com.google.gwt.user.client.ui.Widget;

public class FormField<F extends Widget> extends Composite {
	private final Label label;
	private final F field;
	private final Label errorLabel;

	public FormField(final String name, final F field) {
		label = new Label(name);
		label.addStyleName("field-label");
		errorLabel = new Label();
		errorLabel.addStyleName("error-label");
		errorLabel.setVisible(false);
		this.field = field;
		field.addStyleName("field");

		final HorizontalPanel panel = new HorizontalPanel();
		panel.setVerticalAlignment(HasVerticalAlignment.ALIGN_MIDDLE);
		panel.addStyleName("form-field");
		panel.add(label);
		panel.add(field);
		panel.add(errorLabel);

		initWidget(panel);
	}

	public Label getErrorLabel() {
		return errorLabel;
	}

	public F getField() {
		return field;
	}

	public Label getLabel() {
		return label;
	}
}
