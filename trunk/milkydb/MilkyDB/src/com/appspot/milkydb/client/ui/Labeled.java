package com.appspot.milkydb.client.ui;

import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.HasVerticalAlignment;
import com.google.gwt.user.client.ui.HorizontalPanel;
import com.google.gwt.user.client.ui.Label;
import com.google.gwt.user.client.ui.Widget;

public class Labeled<F extends Widget> extends Composite {
	private final Label label;
	private final F field;

	public Labeled(final String name, final F field) {
		label = new Label(name);
		label.addStyleName("field-label");
		this.field = field;
		field.addStyleName("field");

		final HorizontalPanel panel = new HorizontalPanel();
		panel.setVerticalAlignment(HasVerticalAlignment.ALIGN_MIDDLE);
		panel.addStyleName("labeled-field");
		panel.add(label);
		panel.add(field);

		initWidget(panel);
	}

	public F getField() {
		return field;
	}

	public Label getLabel() {
		return label;
	}
}
