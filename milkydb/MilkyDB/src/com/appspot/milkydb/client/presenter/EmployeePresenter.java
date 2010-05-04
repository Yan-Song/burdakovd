package com.appspot.milkydb.client.presenter;

import java.util.ArrayList;
import java.util.List;

import com.appspot.milkydb.client.services.MilkyServiceAsync;
import com.appspot.milkydb.shared.LightEmployeeDetails;
import com.google.gwt.user.client.Window;
import com.google.gwt.user.client.rpc.AsyncCallback;
import com.google.gwt.user.client.ui.HasWidgets;
import com.google.gwt.user.client.ui.Widget;

public class EmployeePresenter implements Presenter {

	public interface Display {
		Widget asWidget();

		void setData(final List<LightEmployeeDetails> employees);
	}

	private final Display display;
	private final MilkyServiceAsync service;

	public EmployeePresenter(final Display display,
			final MilkyServiceAsync service) {
		this.display = display;
		this.service = service;
	}

	private void fetchEmployeeList() {
		service
				.getEmployeeList(new AsyncCallback<ArrayList<LightEmployeeDetails>>() {

					@Override
					public void onFailure(final Throwable caught) {
						Window.alert("Can't fetch employee list");
					}

					@Override
					public void onSuccess(
							final ArrayList<LightEmployeeDetails> result) {
						display.setData(result);
					}
				});
	}

	@Override
	public void go(final HasWidgets container) {
		container.clear();
		container.add(display.asWidget());
		fetchEmployeeList();
	}
}
