package com.appspot.milkydb.server.services;

import com.appspot.milkydb.server.models.FinalProductClass;

public class GetFinalProductClassesHandler extends
		AbstractGetProductClassesHandler<FinalProductClass> {

	public GetFinalProductClassesHandler() {
		super(FinalProductClass.class);
	}

}
