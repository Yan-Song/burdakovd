package com.appspot.milkydb.server;

import com.appspot.milkydb.shared.Squarer;
import com.google.gwt.user.server.rpc.RemoteServiceServlet;

@SuppressWarnings("serial")
public class SquarerImpl extends RemoteServiceServlet implements Squarer {

	@Override
	public Integer Sqr(final Integer x) {
		return x * x;
	}

}
