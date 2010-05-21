package com.appspot.milkydb.server.services;

import com.appspot.milkydb.server.models.RawMaterialClass;

public class GetRawMaterialClassesHandler extends
		AbstractGetProductClassesHandler<RawMaterialClass> {

	public GetRawMaterialClassesHandler() {
		super(RawMaterialClass.class);
	}

}
