package com.appspot.milkydb.shared.services;

import java.io.Serializable;

import com.google.gwt.user.client.rpc.RemoteService;
import com.google.gwt.user.client.rpc.RemoteServiceRelativePath;

@RemoteServiceRelativePath("milkyService")
public interface MilkyService extends RemoteService {
	<Req extends Serializable, Resp extends Serializable> Resp execute(
			Action<Req, Resp> action, Req request);
}
