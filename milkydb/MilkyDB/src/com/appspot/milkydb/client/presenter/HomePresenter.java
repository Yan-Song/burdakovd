package com.appspot.milkydb.client.presenter;

import com.google.gwt.user.client.ui.HasWidgets;
import com.google.gwt.user.client.ui.Widget;

public class HomePresenter implements Presenter {

	public interface Display {
		Widget asWidget();
	}

	private final Display display;

	public HomePresenter(final Display display) {
		this.display = display;
	}

	@Override
	public void go(final HasWidgets container) {
		container.add(display.asWidget());
	}
}
