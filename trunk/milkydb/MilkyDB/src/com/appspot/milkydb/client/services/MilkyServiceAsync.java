package com.appspot.milkydb.client.services;

import java.util.ArrayList;

import com.appspot.milkydb.shared.LightEmployeeDetails;
import com.google.gwt.user.client.rpc.AsyncCallback;

public interface MilkyServiceAsync {

	void getEmployeeList(AsyncCallback<ArrayList<LightEmployeeDetails>> callback);

}
