package com.appspot.milkydb.shared;

import com.google.gwt.user.client.rpc.AsyncCallback;

public interface SquarerAsync {

	void Sqr(Integer x, AsyncCallback<Integer> callback);

}
