package com.appspot.milkydb.shared.service;

import com.appspot.milkydb.client.validation.ValidationError;
import com.appspot.milkydb.shared.dto.RpcRequest;
import com.appspot.milkydb.shared.dto.RpcResponse;
import com.appspot.milkydb.shared.service.action.Action;
import com.google.gwt.user.client.rpc.RemoteService;
import com.google.gwt.user.client.rpc.RemoteServiceRelativePath;

@RemoteServiceRelativePath("milkyService")
public interface MilkyService extends RemoteService {
	<Req extends RpcRequest, Resp extends RpcResponse> Resp execute(
			Action<Req, Resp> action, Req request) throws ValidationError;
}
