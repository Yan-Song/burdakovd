package com.appspot.milkydb.client;

import com.appspot.milkydb.client.presenter.ApplicationPresenter;
import com.appspot.milkydb.client.services.MilkyService;
import com.appspot.milkydb.client.services.MilkyServiceAsync;
import com.appspot.milkydb.client.view.ApplicationView;
import com.google.gwt.core.client.EntryPoint;
import com.google.gwt.core.client.GWT;
import com.google.gwt.event.shared.HandlerManager;
import com.google.gwt.user.client.DOM;
import com.google.gwt.user.client.ui.RootLayoutPanel;
import com.google.gwt.user.client.ui.RootPanel;

public class MilkyClient implements EntryPoint {

	@Override
	public void onModuleLoad() {
		final HandlerManager eventBus = new HandlerManager(null);
		final MilkyServiceAsync service = GWT.create(MilkyService.class);
		final ApplicationPresenter app = new ApplicationPresenter(eventBus,
				service, new ApplicationView());

		removeLoading();
		app.go(RootLayoutPanel.get());
	}

	private void removeLoading() {
		DOM.removeChild(RootPanel.getBodyElement(), DOM
				.getElementById("loading"));
	}
}
