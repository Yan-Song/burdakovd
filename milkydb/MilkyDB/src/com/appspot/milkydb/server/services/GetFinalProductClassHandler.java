package com.appspot.milkydb.server.services;

import com.appspot.milkydb.server.models.FinalProductClass;

public class GetFinalProductClassHandler extends
		AbstractGetProductClassHandler<FinalProductClass> {

	public GetFinalProductClassHandler() {
		super(FinalProductClass.class);
	}
}
