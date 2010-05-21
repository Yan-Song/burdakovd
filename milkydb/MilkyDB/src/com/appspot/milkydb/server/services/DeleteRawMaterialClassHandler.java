package com.appspot.milkydb.server.services;

import com.appspot.milkydb.server.models.RawMaterialClass;
import com.appspot.milkydb.shared.dto.EncodedKeys;
import com.appspot.milkydb.shared.dto.RpcVoid;

public class DeleteRawMaterialClassHandler extends
		AbstractDeleteEntitiesHandler<RawMaterialClass> implements
		ActionHandler<EncodedKeys, RpcVoid> {

	public DeleteRawMaterialClassHandler() {
		super(RawMaterialClass.class);
	}
}
