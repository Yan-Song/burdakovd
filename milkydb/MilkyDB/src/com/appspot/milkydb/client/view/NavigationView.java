package com.appspot.milkydb.client.view;

import java.util.List;

import com.appspot.milkydb.client.presenter.NavigationPresenter;
import com.appspot.milkydb.client.presenter.NavigationPresenter.NavigationLink;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.Hyperlink;
import com.google.gwt.user.client.ui.VerticalPanel;
import com.google.gwt.user.client.ui.Widget;

public class NavigationView extends Composite implements
		NavigationPresenter.Display {

	private final VerticalPanel panel = new VerticalPanel();

	public NavigationView() {
		initWidget(panel);
	}

	@Override
	public Widget asWidget() {
		return this;
	}

	@Override
	public void setData(final List<NavigationLink> links, final String token) {
		panel.clear();
		for (final NavigationLink link : links) {
			final Hyperlink hyperlink = new Hyperlink(link.text, link.token);

			if (token.startsWith(link.token)) {
				hyperlink.addStyleDependentName("selected");
			}

			panel.add(hyperlink);
		}
	}
}
