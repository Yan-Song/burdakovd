package com.appspot.milkydb.client.ui;

import java.util.ArrayList;
import java.util.List;

import com.google.gwt.event.logical.shared.ValueChangeEvent;
import com.google.gwt.event.logical.shared.ValueChangeHandler;
import com.google.gwt.event.shared.HandlerManager;
import com.google.gwt.event.shared.HandlerRegistration;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.HasValue;
import com.google.gwt.user.client.ui.ListBox;

public class FreeListBox extends Composite implements HasValue<String> {
	private final static String add = "Создать...";
	private final ListBox listBox = new ListBox();
	private final HandlerManager handlerManager = new HandlerManager(this);

	public FreeListBox() {
		initWidget(listBox);
		setData(new ArrayList<String>());
	}

	@Override
	public HandlerRegistration addValueChangeHandler(
			final ValueChangeHandler<String> handler) {

		return handlerManager.addHandler(ValueChangeEvent.getType(), handler);
	}

	@Override
	public String getValue() {
		final int i = listBox.getSelectedIndex();
		return i == -1 ? null : listBox.getItemText(i);
	}

	public void setData(final List<String> data) {
		final String old = getValue();

		listBox.clear();

		for (final String v : data) {
			listBox.addItem(v);
		}

		listBox.addItem(add);

		listBox.setSelectedIndex(-1);
		if (old != null) {
			for (int i = 0; i < listBox.getItemCount(); ++i) {
				if (listBox.getItemText(i).equals(old)) {
					listBox.setSelectedIndex(i);
					break;
				}
			}
		}
	}

	@Override
	public void setValue(final String value) {
		for (int i = 0; i < listBox.getItemCount(); ++i) {
			if (listBox.getItemText(i).equals(value)) {
				listBox.setSelectedIndex(i);
				return;
			}
		}
		listBox.addItem(value);
		listBox.setSelectedIndex(listBox.getItemCount() - 1);
	}

	@Override
	public void setValue(final String value, final boolean fireEvents) {
		setValue(value);

		if (fireEvents) {
			ValueChangeEvent.<String> fire(this, getValue());
		}
	}
}
