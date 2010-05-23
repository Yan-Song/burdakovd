package com.appspot.milkydb.server.services;

import com.appspot.milkydb.server.models.RawMaterialClass;

public class DeleteRawMaterialClassHandler extends
		AbstractDeleteEntitiesHandler<RawMaterialClass> {

	public DeleteRawMaterialClassHandler() {
		super(RawMaterialClass.class);
	}
}
