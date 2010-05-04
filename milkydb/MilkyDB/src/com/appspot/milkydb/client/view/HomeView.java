package com.appspot.milkydb.client.view;

import com.appspot.milkydb.client.presenter.HomePresenter;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.FlowPanel;
import com.google.gwt.user.client.ui.Label;
import com.google.gwt.user.client.ui.Widget;

public class HomeView extends Composite implements HomePresenter.Display {
	private final FlowPanel content = new FlowPanel();

	public HomeView() {
		content.add(new Label("Ла-ла-ла. Навигация слева."));
		initWidget(content);
	}

	@Override
	public Widget asWidget() {
		return this;
	}

}
