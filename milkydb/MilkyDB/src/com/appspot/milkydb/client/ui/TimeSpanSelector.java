package com.appspot.milkydb.client.ui;

import com.appspot.milkydb.shared.dto.TimeSpan;
import com.google.gwt.event.dom.client.ChangeEvent;
import com.google.gwt.event.dom.client.ChangeHandler;
import com.google.gwt.event.logical.shared.ValueChangeEvent;
import com.google.gwt.event.logical.shared.ValueChangeHandler;
import com.google.gwt.event.shared.HandlerRegistration;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.HasValue;
import com.google.gwt.user.client.ui.HorizontalPanel;
import com.google.gwt.user.client.ui.ListBox;
import com.google.gwt.user.client.ui.TextBox;

public class TimeSpanSelector extends Composite implements HasValue<TimeSpan> {

	private final TextBox textBox = new TextBox();
	private final ListBox units = new ListBox() {
		{
			addItem("часы", "3600");
			addItem("сутки", String.valueOf(3600 * 24));
			addItem("недели", String.valueOf(3600 * 24 * 7));
			addItem("месяцы", String.valueOf(3600 * 24 * 30));
			setSelectedIndex(1);
		}
	};
	private final HorizontalPanel panel = new HorizontalPanel() {
		{
			add(textBox);
			add(units);
		}
	};

	TimeSpan oldValue = null;

	public TimeSpanSelector() {
		initWidget(panel);
		doFireEvents();
		bind();
	}

	@Override
	public HandlerRegistration addValueChangeHandler(
			final ValueChangeHandler<TimeSpan> handler) {
		return addHandler(handler, ValueChangeEvent.getType());
	}

	private void bind() {
		textBox.addValueChangeHandler(new ValueChangeHandler<String>() {
			@Override
			public void onValueChange(final ValueChangeEvent<String> event) {
				doFireEvents();
			}
		});

		units.addChangeHandler(new ChangeHandler() {

			@Override
			public void onChange(final ChangeEvent event) {
				doFireEvents();
			}
		});
	}

	private void doFireEvents() {
		final TimeSpan newValue = getValue();
		ValueChangeEvent.fireIfNotEqual(this, oldValue, newValue);
		oldValue = newValue;
	}

	private long getCurrentUnitInSeconds() {
		return Long.parseLong(units.getValue(units.getSelectedIndex()));
	}

	@Override
	public TimeSpan getValue() {
		try {
			final long milliseconds = Long.parseLong(textBox.getValue())
					* getCurrentUnitInSeconds() * 1000l;
			return new TimeSpan(milliseconds);
		} catch (final NumberFormatException e) {
			return null;
		}
	}

	@Override
	public void setValue(final TimeSpan value) {
		final long seconds = value.getSeconds();

		int unitIndex;
		if (seconds < 3600 * 72) {
			unitIndex = 0;
		} else if (seconds < 3600 * 24 * 21) {
			unitIndex = 1;
		} else if (seconds < 3600 * 24 * 7 * 12) {
			unitIndex = 2;
		} else {
			unitIndex = 3;
		}

		units.setSelectedIndex(unitIndex);
		textBox.setValue(String.valueOf(seconds / getCurrentUnitInSeconds()));
	}

	@Override
	public void setValue(final TimeSpan value, final boolean fireEvents) {
		setValue(value);

		if (fireEvents) {
			doFireEvents();
		}
	}

}
