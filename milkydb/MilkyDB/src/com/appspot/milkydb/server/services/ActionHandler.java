package com.appspot.milkydb.server.services;

public interface ActionHandler<Req, Resp> {
	Resp execute(Req request);
}
