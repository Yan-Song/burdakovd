package com.appspot.milkydb.server.services;

import com.appspot.milkydb.server.models.FinalProductClass;

public class DeleteFinalProductClassHandler extends
		AbstractDeleteEntitiesHandler<FinalProductClass> {

	public DeleteFinalProductClassHandler() {
		super(FinalProductClass.class);
	}

}
