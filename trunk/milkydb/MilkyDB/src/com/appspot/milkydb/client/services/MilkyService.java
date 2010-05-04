package com.appspot.milkydb.client.services;

import java.util.ArrayList;

import com.appspot.milkydb.shared.LightEmployeeDetails;
import com.google.gwt.user.client.rpc.RemoteService;
import com.google.gwt.user.client.rpc.RemoteServiceRelativePath;

@RemoteServiceRelativePath("milkyService")
public interface MilkyService extends RemoteService {
	ArrayList<LightEmployeeDetails> getEmployeeList();
}
