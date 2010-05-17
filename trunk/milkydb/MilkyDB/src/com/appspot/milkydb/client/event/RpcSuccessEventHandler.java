package com.appspot.milkydb.client.event;

import com.google.gwt.event.shared.EventHandler;

public interface RpcSuccessEventHandler extends EventHandler {

	void onRpcSuccess(RpcSuccessEvent rpcSuccessEvent);

}
