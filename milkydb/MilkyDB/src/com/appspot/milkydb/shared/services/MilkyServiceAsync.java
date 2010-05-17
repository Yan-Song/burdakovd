package com.appspot.milkydb.shared.services;

import java.io.Serializable;

import com.google.gwt.user.client.rpc.AsyncCallback;

public interface MilkyServiceAsync {

	<Req extends Serializable, Resp extends Serializable> void execute(
			Action<Req, Resp> action, Req request, AsyncCallback<Resp> callback);

}
