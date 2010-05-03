package com.appspot.milkydb.client.view;

import com.appspot.milkydb.client.presenter.ApplicationPresenter.Display;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.FlowPanel;
import com.google.gwt.user.client.ui.HasWidgets;
import com.google.gwt.user.client.ui.SimplePanel;
import com.google.gwt.user.client.ui.SplitLayoutPanel;
import com.google.gwt.user.client.ui.Widget;

public class ApplicationView extends Composite implements Display {

	final SimplePanel navigationPanel = new SimplePanel();
	final FlowPanel contentPanel = new FlowPanel();

	public ApplicationView() {
		final SplitLayoutPanel splitter = new SplitLayoutPanel();
		splitter.addWest(navigationPanel, 200);
		splitter.add(contentPanel);
		initWidget(splitter);
	}

	@Override
	public Widget asWidget() {
		return this;
	}

	@Override
	public HasWidgets getContentPanel() {
		return contentPanel;
	}

	@Override
	public HasWidgets getNavigationPanel() {
		return navigationPanel;
	}

}
