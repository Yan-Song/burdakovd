package com.appspot.milkydb.shared.service.action;

import com.appspot.milkydb.shared.dto.Dto;
import com.appspot.milkydb.shared.dto.DtoList;
import com.appspot.milkydb.shared.dto.KeyList;
import com.appspot.milkydb.shared.dto.LightEmployee;
import com.appspot.milkydb.shared.dto.LightProductClass;
import com.appspot.milkydb.shared.dto.RpcVoid;
import com.appspot.milkydb.shared.dto.SingleKey;
import com.appspot.milkydb.shared.models.BaseProductClass;
import com.appspot.milkydb.shared.models.Employee;

public class ManagerActionSet<LightDto extends Dto, FullDto extends Dto> {

	public static ManagerActionSet<LightEmployee, Employee> Employee = new ManagerActionSet<LightEmployee, Employee>(
			"Employee");

	public static ManagerActionSet<LightProductClass, BaseProductClass> RawMaterialClass = new ManagerActionSet<LightProductClass, BaseProductClass>(
			"RawMaterialClass");

	public static ManagerActionSet<LightProductClass, BaseProductClass> FinalProductClass = new ManagerActionSet<LightProductClass, BaseProductClass>(
			"FinalProductClass");

	private final Action<RpcVoid, DtoList<LightDto>> getAll;
	private final Action<SingleKey, FullDto> get;
	private final Action<FullDto, SingleKey> save;
	private final Action<KeyList, RpcVoid> delete;

	ManagerActionSet(final String name) {
		getAll = new Action<RpcVoid, DtoList<LightDto>>(name + "::getAll");
		get = new Action<SingleKey, FullDto>(name + "::get");
		save = new Action<FullDto, SingleKey>(name + "::save");
		delete = new Action<KeyList, RpcVoid>(name + "::delete");
	}

	public Action<KeyList, RpcVoid> provideDeleteAction() {
		return delete;
	}

	public Action<SingleKey, FullDto> provideGetAction() {
		return get;
	}

	public Action<RpcVoid, DtoList<LightDto>> provideGetAllAction() {
		return getAll;
	}

	public Action<FullDto, SingleKey> provideSaveAction() {
		return save;
	}
}
