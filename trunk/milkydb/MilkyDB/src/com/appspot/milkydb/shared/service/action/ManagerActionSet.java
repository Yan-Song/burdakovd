package com.appspot.milkydb.shared.service.action;

import com.appspot.milkydb.shared.dto.Dto;
import com.appspot.milkydb.shared.dto.DtoList;
import com.appspot.milkydb.shared.dto.EncodedKey;
import com.appspot.milkydb.shared.dto.EncodedKeys;
import com.appspot.milkydb.shared.dto.FullEmployee;
import com.appspot.milkydb.shared.dto.FullProductClass;
import com.appspot.milkydb.shared.dto.LightEmployee;
import com.appspot.milkydb.shared.dto.LightProductClass;
import com.appspot.milkydb.shared.dto.RpcVoid;

public class ManagerActionSet<LightDto extends Dto, FullDto extends Dto> {

	public static ManagerActionSet<LightEmployee, FullEmployee> Employee = new ManagerActionSet<LightEmployee, FullEmployee>(
			"Employee");

	public static ManagerActionSet<LightProductClass, FullProductClass> RawMaterialClass = new ManagerActionSet<LightProductClass, FullProductClass>(
			"RawMaterialClass");

	public static ManagerActionSet<LightProductClass, FullProductClass> FinalProductClass = new ManagerActionSet<LightProductClass, FullProductClass>(
			"FinalProductClass");

	private final Action<RpcVoid, DtoList<LightDto>> getAll;
	private final Action<EncodedKey, FullDto> get;
	private final Action<FullDto, EncodedKey> save;
	private final Action<EncodedKeys, RpcVoid> delete;

	ManagerActionSet(final String name) {
		getAll = new Action<RpcVoid, DtoList<LightDto>>(name + "::getAll");
		get = new Action<EncodedKey, FullDto>(name + "::get");
		save = new Action<FullDto, EncodedKey>(name + "::save");
		delete = new Action<EncodedKeys, RpcVoid>(name + "::delete");
	}

	public Action<EncodedKeys, RpcVoid> provideDeleteAction() {
		return delete;
	}

	public Action<EncodedKey, FullDto> provideGetAction() {
		return get;
	}

	public Action<RpcVoid, DtoList<LightDto>> provideGetAllAction() {
		return getAll;
	}

	public Action<FullDto, EncodedKey> provideSaveAction() {
		return save;
	}
}
