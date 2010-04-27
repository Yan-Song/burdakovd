package com.appspot.milkydb.client;

import com.appspot.milkydb.shared.Squarer;
import com.appspot.milkydb.shared.SquarerAsync;
import com.google.gwt.core.client.EntryPoint;
import com.google.gwt.core.client.GWT;
import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.user.client.rpc.AsyncCallback;
import com.google.gwt.user.client.rpc.ServiceDefTarget;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.Label;
import com.google.gwt.user.client.ui.RootPanel;
import com.google.gwt.user.client.ui.TextBox;

public class MilkyClient implements EntryPoint {
	@Override
	public void onModuleLoad() {

		final Label label = new Label("Input number: ");
		final TextBox text = new TextBox();
		final Button button = new Button("SQR!");
		final Label result = new Label();

		final SquarerAsync squarer = (SquarerAsync) GWT.create(Squarer.class);
		((ServiceDefTarget) squarer).setServiceEntryPoint("/rpc/squarer");

		button.addClickHandler(new ClickHandler() {
			@Override
			public void onClick(final ClickEvent event) {
				text.setEnabled(false);
				button.setEnabled(false);

				squarer.Sqr(Integer.parseInt(text.getText()),
						new AsyncCallback<Integer>() {

							@Override
							public void onFailure(final Throwable caught) {
								result.setText("Fail!!! :( "
										+ caught.getLocalizedMessage());
								text.setEnabled(true);
								button.setEnabled(true);
							}

							@Override
							public void onSuccess(final Integer res) {
								result.setText("SQR(" + text.getText() + ") = "
										+ res.toString());
								text.setEnabled(true);
								button.setEnabled(true);
							}

						});
			}
		});

		RootPanel.get("approot").add(label);
		RootPanel.get("approot").add(text);
		RootPanel.get("approot").add(button);
		RootPanel.get("approot").add(result);

	}
}
