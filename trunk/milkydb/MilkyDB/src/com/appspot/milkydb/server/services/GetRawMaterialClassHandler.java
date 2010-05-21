package com.appspot.milkydb.server.services;

import com.appspot.milkydb.server.models.RawMaterialClass;

public class GetRawMaterialClassHandler extends
		AbstractGetProductClassHandler<RawMaterialClass> {

	public GetRawMaterialClassHandler() {
		super(RawMaterialClass.class);
	}
}
