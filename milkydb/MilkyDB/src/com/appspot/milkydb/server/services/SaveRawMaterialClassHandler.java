package com.appspot.milkydb.server.services;

import com.appspot.milkydb.server.models.RawMaterialClass;

public class SaveRawMaterialClassHandler extends
		AbstractSaveProductClassHandler<RawMaterialClass> {

	public SaveRawMaterialClassHandler() {
		super(RawMaterialClass.class);
	}

}
