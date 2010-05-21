package com.appspot.milkydb.server.services;

import com.appspot.milkydb.client.validation.ValidationError;
import com.appspot.milkydb.shared.dto.RpcRequest;
import com.appspot.milkydb.shared.dto.RpcResponse;

public interface ActionHandler<Req extends RpcRequest, Resp extends RpcResponse> {
	Resp execute(Req request) throws ValidationError;
}
