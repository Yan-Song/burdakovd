package com.appspot.milkydb.client.view;

import com.appspot.milkydb.client.presenter.ApplicationPresenter.Display;
import com.google.gwt.dom.client.Style.Unit;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.DockLayoutPanel;
import com.google.gwt.user.client.ui.FlowPanel;
import com.google.gwt.user.client.ui.HasWidgets;
import com.google.gwt.user.client.ui.SimplePanel;
import com.google.gwt.user.client.ui.Widget;

public class ApplicationView extends Composite implements Display {

	final SimplePanel navigationPanel = new SimplePanel() {
		{
			addStyleName("navigation");
		}
	};

	final FlowPanel contentPanel = new FlowPanel() {
		{
			addStyleName("content");
		}
	};

	public ApplicationView() {
		final DockLayoutPanel panel = new DockLayoutPanel(Unit.EM);
		panel.addWest(navigationPanel, 15);
		panel.add(contentPanel);
		panel.addStyleName("application");
		initWidget(panel);
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
