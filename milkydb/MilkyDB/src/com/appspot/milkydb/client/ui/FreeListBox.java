package com.appspot.milkydb.client.ui;

import java.util.ArrayList;
import java.util.List;

import com.google.gwt.event.dom.client.ChangeEvent;
import com.google.gwt.event.dom.client.ChangeHandler;
import com.google.gwt.event.logical.shared.ValueChangeEvent;
import com.google.gwt.event.logical.shared.ValueChangeHandler;
import com.google.gwt.event.shared.HandlerManager;
import com.google.gwt.event.shared.HandlerRegistration;
import com.google.gwt.user.client.Window;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.HasValue;
import com.google.gwt.user.client.ui.ListBox;

public class FreeListBox extends Composite implements HasValue<String> {
	private final static String createText = "Создать...";
	private final static String notSelectedText = "(не выбрано)";
	private final ListBox listBox = new ListBox();
	private final HandlerManager handlerManager = new HandlerManager(this);

	public FreeListBox() {
		initWidget(listBox);
		setVariants(new ArrayList<String>(), false);
		setValue(null);

		bind();
	}

	private void bind() {
		listBox.addChangeHandler(new ChangeHandler() {
			@Override
			public void onChange(final ChangeEvent event) {
				onListboxChange(event);
			}
		});
	}

	@Override
	public HandlerRegistration addValueChangeHandler(
			final ValueChangeHandler<String> handler) {

		return handlerManager.addHandler(ValueChangeEvent.getType(), handler);
	}

	@Override
	public String getValue() {
		final int i = listBox.getSelectedIndex();
		assert i < listBox.getItemCount() - 1;
		return i == 0 ? null : listBox.getItemText(i);
	}

	private void onListboxChange(final ChangeEvent event) {
		if (listBox.getSelectedIndex() == listBox.getItemCount() - 1) {
			final String s = Window.prompt("Введите новое значение", "");
			if (s != null && !s.isEmpty()) {
				setValue(s, true);
			} else {
				setValue(null, true);
			}
		} else {
			ValueChangeEvent.<String> fire(this, getValue());
		}
	}

	@Override
	/*
	 * Устанавливает новый выбранный элемент. Если в новом списке нет текущего
	 * итема, то он туда добавляется.
	 */
	public void setValue(final String value) {
		if (value == null) {
			listBox.setSelectedIndex(0);
			return;
		}

		for (int i = 1; i < listBox.getItemCount() - 1; ++i) {
			if (listBox.getItemText(i).equals(value)) {
				listBox.setSelectedIndex(i);
				return;
			}
		}

		listBox.insertItem(value, listBox.getItemCount() - 1);
		listBox.setSelectedIndex(listBox.getItemCount() - 2);
	}

	@Override
	public void setValue(final String value, final boolean fireEvents) {
		setValue(value);

		if (fireEvents) {
			ValueChangeEvent.<String> fire(this, getValue());
		}
	}

	/*
	 * Загружает список вариантов. Больше ничего не делает, текущий выбранный
	 * элемент в списке может не соответствовать новым данным.
	 */
	private void setVariants(final List<String> variants) {
		listBox.clear();

		listBox.addItem(notSelectedText);
		for (final String v : variants) {
			listBox.addItem(v);
		}
		listBox.addItem(createText);
	}

	/*
	 * Если установлен флаг saveCurrentSelection, то не портит текущего
	 * выбранного итема. Если в новом списке нет текущего итема, то он туда
	 * добавляется.
	 * 
	 * Иначе сбрасывает выделение.
	 */
	private void setVariants(final List<String> variants,
			final boolean saveCurrentSelection) {

		if (saveCurrentSelection) {
			final String old = getValue();
			setVariants(variants);
			setValue(old);
		} else {
			setVariants(variants);
			setValue(null);
		}
	}
}
