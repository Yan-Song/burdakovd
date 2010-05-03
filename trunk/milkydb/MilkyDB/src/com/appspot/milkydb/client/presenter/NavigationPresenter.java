package com.appspot.milkydb.client.presenter;

import java.util.ArrayList;
import java.util.List;

import com.google.gwt.event.logical.shared.ValueChangeEvent;
import com.google.gwt.event.logical.shared.ValueChangeHandler;
import com.google.gwt.user.client.History;
import com.google.gwt.user.client.ui.HasWidgets;
import com.google.gwt.user.client.ui.Widget;

@SuppressWarnings("serial")
public class NavigationPresenter implements Presenter,
		ValueChangeHandler<String> {

	public interface Display {
		Widget asWidget();

		void setData(final List<NavigationLink> links, final String token);
	}

	public class NavigationLink {
		public String token;
		public String text;

		public NavigationLink(final String token, final String text) {
			this.token = token;
			this.text = text;
		}
	}

	private final List<NavigationLink> menuLinks = new ArrayList<NavigationLink>() {
		{
			add(new NavigationLink("home", "Домашняя страница"));
		}
	};

	private final Display display;

	public NavigationPresenter(final Display display) {
		this.display = display;
		bind();
	}

	private void bind() {
		History.addValueChangeHandler(this);
	}

	@Override
	public void go(final HasWidgets container) {
		container.clear();
		container.add(display.asWidget());
	}

	@Override
	public void onValueChange(final ValueChangeEvent<String> event) {
		display.setData(menuLinks, History.getToken());
	}

}
