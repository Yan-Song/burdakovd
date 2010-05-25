package com.appspot.milkydb.client.ui;

import java.util.HashSet;
import java.util.Set;

import com.google.gwt.event.dom.client.ChangeEvent;
import com.google.gwt.event.dom.client.ChangeHandler;
import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.event.logical.shared.ValueChangeEvent;
import com.google.gwt.event.logical.shared.ValueChangeHandler;
import com.google.gwt.event.shared.HandlerRegistration;
import com.google.gwt.user.client.Window;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.HasValue;
import com.google.gwt.user.client.ui.HorizontalPanel;
import com.google.gwt.user.client.ui.ListBox;

public class FreeMultiListBox extends Composite implements
		HasValue<Set<String>> {

	private final ListBox list = new ListBox(true);
	private final Button button = new Button("Другое...");

	private final HorizontalPanel panel = new HorizontalPanel() {
		{
			addStyleName("FreeMultiListBox");
			add(list);
			add(button);
		}
	};

	public FreeMultiListBox() {
		initWidget(panel);

		bind();
	}

	@Override
	public HandlerRegistration addValueChangeHandler(
			final ValueChangeHandler<Set<String>> handler) {
		return addHandler(handler, ValueChangeEvent.getType());
	}

	private void addVariant(final String value) {
		list.addItem(value);
	}

	private void bind() {
		list.addChangeHandler(new ChangeHandler() {

			@Override
			public void onChange(final ChangeEvent event) {
				doFireEvents();
			}
		});

		button.addClickHandler(new ClickHandler() {

			@Override
			public void onClick(final ClickEvent event) {
				onNewVariant();
			}
		});
	}

	private void clear() {
		list.clear();
	}

	private void clearSelection() {
		for (int i = 0; i < list.getItemCount(); ++i) {
			list.setItemSelected(i, false);
		}
	}

	private void doFireEvents() {
		ValueChangeEvent.fire(this, getValue());
	}

	@Override
	public Set<String> getValue() {
		final HashSet<String> ans = new HashSet<String>();
		for (int i = 0; i < list.getItemCount(); ++i) {
			if (list.isItemSelected(i)) {
				ans.add(list.getItemText(i));
			}
		}

		return ans;
	}

	private boolean hasVariant(final String value) {
		for (int i = 0; i < list.getItemCount(); ++i) {
			if (value.equals(list.getItemText(i))) {
				return true;
			}
		}

		return false;
	}

	private void onNewVariant() {
		final String newVariant = Window.prompt("Новое значение", "");
		if (newVariant != null && !newVariant.equals("")
				&& !hasVariant(newVariant)) {
			addVariant(newVariant);
			setSelected(newVariant, true);
		}
	}

	private void setSelected(final String value, final boolean selected) {
		for (int i = 0; i < list.getItemCount(); ++i) {
			if (value.equals(list.getItemText(i))) {
				list.setItemSelected(i, selected);
			}
		}
	}

	@Override
	public void setValue(final Set<String> values) {
		for (final String value : values) {
			if (!hasVariant(value)) {
				addVariant(value);
			}
		}

		clearSelection();

		for (final String value : values) {
			setSelected(value, true);
		}
	}

	@Override
	public void setValue(final Set<String> value, final boolean fireEvents) {
		setValue(value);

		if (fireEvents) {
			doFireEvents();
		}
	}

	public void setVariants(final Set<String> variants) {
		final Set<String> oldValue = getValue();

		clear();
		for (final String variant : variants) {
			addVariant(variant);
		}

		setValue(oldValue);
	}
}
