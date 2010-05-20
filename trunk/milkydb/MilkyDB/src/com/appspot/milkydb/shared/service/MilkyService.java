package com.appspot.milkydb.shared.service;

import java.io.Serializable;

import com.appspot.milkydb.client.validation.ValidationError;
import com.google.gwt.user.client.rpc.RemoteService;
import com.google.gwt.user.client.rpc.RemoteServiceRelativePath;

@RemoteServiceRelativePath("milkyService")
public interface MilkyService extends RemoteService {
	<Req extends Serializable, Resp extends Serializable> Resp execute(
			Action<Req, Resp> action, Req request) throws ValidationError;
}
