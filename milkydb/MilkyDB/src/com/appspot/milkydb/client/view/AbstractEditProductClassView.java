package com.appspot.milkydb.client.view;

import java.util.HashMap;
import java.util.Map;

import com.appspot.milkydb.client.presenter.AbstractEditProductClassPresenter;
import com.appspot.milkydb.client.ui.FormField;
import com.appspot.milkydb.client.ui.FreeMultiListBox;
import com.appspot.milkydb.client.ui.TimeSpanSelector;
import com.appspot.milkydb.shared.dto.FullProductClass;
import com.appspot.milkydb.shared.dto.TimeSpan;
import com.google.gwt.user.client.ui.HasValue;
import com.google.gwt.user.client.ui.TextArea;
import com.google.gwt.user.client.ui.TextBox;

public abstract class AbstractEditProductClassView extends AbstractEditView
		implements AbstractEditProductClassPresenter.Display {

	private final FormField<TextBox> name = new FormField<TextBox>("Название",
			new TextBox());

	private final FormField<TextBox> fatness = new FormField<TextBox>(
			"Жирность, %", new TextBox());

	private final FormField<TextBox> calorificValue = new FormField<TextBox>(
			"Энергетическая ценность", new TextBox());

	private final FormField<TextBox> packing = new FormField<TextBox>(
			"Форма упаковки", new TextBox());

	private final FormField<TextArea> storageConstraints = new FormField<TextArea>(
			"Условия хранения", new TextArea());

	private final FormField<TextArea> transportationConstraints = new FormField<TextArea>(
			"Условия транспортировки", new TextArea());

	private final FormField<FreeMultiListBox> ferments = new FormField<FreeMultiListBox>(
			"Ферменты (выберите нужные)", new FreeMultiListBox());

	private final FormField<FreeMultiListBox> microElements = new FormField<FreeMultiListBox>(
			"Микроэлементы (выберите нужные)", new FreeMultiListBox());

	private final FormField<TimeSpanSelector> storageLife = new FormField<TimeSpanSelector>(
			"Срок хранения", new TimeSpanSelector());

	public AbstractEditProductClassView() {
		super();
		initForm(new FormField<?>[] { name, fatness, calorificValue, packing,
				storageLife, storageConstraints, transportationConstraints,
				ferments, microElements });
	}

	@Override
	public HasValue<String> getCalorificValue() {
		return calorificValue.getField();
	}

	@Override
	public HasValue<String> getFatness() {
		return fatness.getField();
	}

	@Override
	public FreeMultiListBox getFerments() {
		return ferments.getField();
	}

	@SuppressWarnings("serial")
	@Override
	protected Map<String, FormField<?>> getFieldsMap() {
		return new HashMap<String, FormField<?>>() {
			{
				put(FullProductClass.Fields.name, name);
				put(FullProductClass.Fields.fatness, fatness);
				put(FullProductClass.Fields.calorificValue, calorificValue);
				put(FullProductClass.Fields.ferments, ferments);
				put(FullProductClass.Fields.microElements, microElements);
				put(FullProductClass.Fields.packing, packing);
				put(FullProductClass.Fields.storageConstraints,
						storageConstraints);
				put(FullProductClass.Fields.storageLife, storageLife);
				put(FullProductClass.Fields.transportationConstraints,
						transportationConstraints);
			}
		};
	}

	@Override
	public FreeMultiListBox getMicroElements() {
		return microElements.getField();
	}

	@Override
	public HasValue<String> getName() {
		return name.getField();
	}

	@Override
	public HasValue<String> getPacking() {
		return packing.getField();
	}

	@Override
	public HasValue<String> getStorageConstraints() {
		return storageConstraints.getField();
	}

	@Override
	public HasValue<TimeSpan> getStorageLife() {
		return storageLife.getField();
	}

	@Override
	public HasValue<String> getTransportationConstraints() {
		return transportationConstraints.getField();
	}

}
