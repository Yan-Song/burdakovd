package com.appspot.milkydb.shared.service;

import com.appspot.milkydb.shared.dto.RpcRequest;
import com.appspot.milkydb.shared.dto.RpcResponse;
import com.appspot.milkydb.shared.service.action.Action;
import com.google.gwt.user.client.rpc.AsyncCallback;

public interface MilkyServiceAsync {

	<Req extends RpcRequest, Resp extends RpcResponse> void execute(
			Action<Req, Resp> action, Req request, AsyncCallback<Resp> callback);

}
