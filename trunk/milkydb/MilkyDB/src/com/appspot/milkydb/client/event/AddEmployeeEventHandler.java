package com.appspot.milkydb.client.event;

import com.google.gwt.event.shared.EventHandler;

public interface AddEmployeeEventHandler extends EventHandler {

	public void onAddEmployee(final AddEmployeeEvent addEmployeeEvent);

}
