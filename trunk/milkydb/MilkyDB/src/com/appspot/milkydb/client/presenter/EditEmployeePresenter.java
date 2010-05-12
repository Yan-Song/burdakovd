package com.appspot.milkydb.client.presenter;

import com.appspot.milkydb.shared.services.MilkyServiceAsync;
import com.google.gwt.event.dom.client.HasClickHandlers;
import com.google.gwt.event.shared.HandlerManager;
import com.google.gwt.user.client.ui.HasValue;
import com.google.gwt.user.client.ui.HasWidgets;
import com.google.gwt.user.client.ui.Widget;

public class EditEmployeePresenter implements Presenter {

	public interface Display {
		Widget asWidget();

		HasClickHandlers getCancelButton();

		HasValue<String> getName();

		HasValue<String> getPost();

		HasValue<String> getSalary();

		HasClickHandlers getSubmitButton();
	}

	private final Display display;
	private final MilkyServiceAsync service;
	private final HandlerManager eventBus;

	public EditEmployeePresenter(final Display editEmployeeView,
			final MilkyServiceAsync service, final HandlerManager eventBus) {
		this.display = editEmployeeView;
		this.service = service;
		this.eventBus = eventBus;

		bind();
	}

	private void bind() {

	}

	@Override
	public void go(final HasWidgets container) {
		container.clear();
		container.add(display.asWidget());
	}

}
