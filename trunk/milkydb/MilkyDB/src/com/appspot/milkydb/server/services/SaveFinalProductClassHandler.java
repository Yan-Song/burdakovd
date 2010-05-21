package com.appspot.milkydb.server.services;

import com.appspot.milkydb.server.models.FinalProductClass;

public class SaveFinalProductClassHandler extends
		AbstractSaveProductClassHandler<FinalProductClass> {

	public SaveFinalProductClassHandler() {
		super(FinalProductClass.class);
	}

}
