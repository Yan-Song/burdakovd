package com.appspot.milkydb.client.event;

import com.google.gwt.event.shared.EventHandler;

public interface EditEmployeeFinishedEventHandler extends EventHandler {

	void onEditEmployeeFinished(
			EditEmployeeFinishedEvent editEmployeeFinishedEvent);

}
