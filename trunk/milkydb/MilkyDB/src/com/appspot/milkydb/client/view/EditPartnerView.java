package com.appspot.milkydb.client.view;

import java.util.HashMap;

import com.appspot.milkydb.client.presenter.AbstractEditPartnerPresenter.Display;
import com.appspot.milkydb.client.ui.FormField;
import com.appspot.milkydb.shared.Validatable.Fields;
import com.appspot.milkydb.shared.models.Partner;
import com.google.gwt.user.client.ui.HasValue;
import com.google.gwt.user.client.ui.TextArea;
import com.google.gwt.user.client.ui.TextBox;

public class EditPartnerView extends AbstractEditEntityView implements Display {

	FormField<TextBox> name = new FormField<TextBox>("Название", new TextBox());
	FormField<TextArea> address = new FormField<TextArea>("Адрес",
			new TextArea());
	FormField<TextBox> phoneNumber = new FormField<TextBox>("Телефон",
			new TextBox());

	public EditPartnerView() {
		initForm(new FormField<?>[] { name, address, phoneNumber });
	}

	@Override
	public HasValue<String> getAddress() {
		return address.getField();
	}

	@SuppressWarnings("serial")
	@Override
	protected HashMap<Enum<? extends Fields>, FormField<?>> getFieldsMap() {
		return new HashMap<Enum<? extends Fields>, FormField<?>>() {
			{
				put(Partner.Fields.address, address);
				put(Partner.Fields.name, name);
				put(Partner.Fields.phoneNumber, phoneNumber);
			}
		};
	}

	@Override
	public HasValue<String> getName() {
		return name.getField();
	}

	@Override
	public HasValue<String> getPhoneNumber() {
		return phoneNumber.getField();
	}

}
