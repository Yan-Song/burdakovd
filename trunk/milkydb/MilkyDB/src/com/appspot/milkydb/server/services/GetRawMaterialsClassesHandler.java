package com.appspot.milkydb.server.services;

import com.appspot.milkydb.server.models.RawMaterialClass;

public class GetRawMaterialsClassesHandler extends
		GetProductClassesHandler<RawMaterialClass> {

	public GetRawMaterialsClassesHandler() {
		super(RawMaterialClass.class);
	}

}
