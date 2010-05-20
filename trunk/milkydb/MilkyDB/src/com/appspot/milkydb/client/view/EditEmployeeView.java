package com.appspot.milkydb.client.view;

import java.util.HashMap;

import com.appspot.milkydb.client.presenter.EditEmployeePresenter;
import com.appspot.milkydb.client.ui.FormField;
import com.appspot.milkydb.client.ui.FreeListBox;
import com.appspot.milkydb.shared.dto.FullEmployee;
import com.google.gwt.user.client.ui.HasValue;
import com.google.gwt.user.client.ui.TextArea;
import com.google.gwt.user.client.ui.TextBox;

@SuppressWarnings("serial")
public class EditEmployeeView extends AbstractEditView implements
		EditEmployeePresenter.Display {

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

	public EditEmployeeView() {
		super();
		initForm(new FormField<?>[] { name, post, salary, address, phone });
	}

	@Override
	public HasValue<String> getAddress() {
		return address.getField();
	}

	@Override
	protected HashMap<String, FormField<?>> getFieldsMap() {
		return new HashMap<String, FormField<?>>() {
			{
				put(FullEmployee.Fields.name, name);
				put(FullEmployee.Fields.post, post);
				put(FullEmployee.Fields.salary, salary);
				put(FullEmployee.Fields.address, address);
				put(FullEmployee.Fields.phoneNumber, phone);
			}
		};
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
}
