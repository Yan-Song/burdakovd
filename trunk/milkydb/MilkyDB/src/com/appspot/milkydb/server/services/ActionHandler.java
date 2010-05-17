package com.appspot.milkydb.server.services;

import com.appspot.milkydb.client.validation.ValidationException;

public interface ActionHandler<Req, Resp> {
	Resp execute(Req request) throws ValidationException;
}
