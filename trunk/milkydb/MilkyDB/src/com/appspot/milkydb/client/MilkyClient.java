package com.appspot.milkydb.client;

import com.google.gwt.core.client.EntryPoint;
import com.google.gwt.user.client.ui.Label;
import com.google.gwt.user.client.ui.RootPanel;
import com.google.gwt.user.client.ui.VerticalPanel;

public class MilkyClient implements EntryPoint {

	final VerticalPanel panel = new VerticalPanel();

	@Override
	public void onModuleLoad() {
		RootPanel.get("slot").add(panel);
		panel.add(new Label("Heldlo!"));
	}
}
