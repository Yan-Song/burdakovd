package com.appspot.milkydb.client.ui;

import com.google.gwt.user.client.ui.HTML;
import com.google.gwt.user.client.ui.PopupPanel;

public class Wait {
	private static PopupPanel wait;

	public static void startWait(final String text) {
		stopWait();

		wait = new PopupPanel(false, true);
		wait.setTitle("Ждите...");

		wait.addStyleName("waitbox");
		wait.setGlassEnabled(true);
		wait.add(new HTML("<div class=\"waitbox-inner\">" + text + "</div>"));
		wait.center();
	}

	public static void stopWait() {
		if (wait != null) {
			wait.hide();
			wait = null;
		}
	}
}
