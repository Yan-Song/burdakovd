package com.appspot.milkydb.client.event;

import com.google.gwt.event.shared.EventHandler;

public interface RpcFailureEventHandler extends EventHandler {

	void onRpcFailure(RpcFailureEvent rpcFailureEvent);

}
