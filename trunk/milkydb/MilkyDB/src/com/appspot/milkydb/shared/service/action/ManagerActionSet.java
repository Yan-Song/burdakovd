package com.appspot.milkydb.shared.service.action;

import com.appspot.milkydb.shared.dto.Dto;
import com.appspot.milkydb.shared.dto.DtoList;
import com.appspot.milkydb.shared.dto.KeyList;
import com.appspot.milkydb.shared.dto.LightEmployee;
import com.appspot.milkydb.shared.dto.RpcVoid;
import com.appspot.milkydb.shared.dto.SingleKey;
import com.appspot.milkydb.shared.models.BaseProductClass;
import com.appspot.milkydb.shared.models.Employee;
import com.appspot.milkydb.shared.models.FinalProductClass;
import com.appspot.milkydb.shared.models.FinalProductReseller;
import com.appspot.milkydb.shared.models.Partner;
import com.appspot.milkydb.shared.models.RawMaterialClass;
import com.appspot.milkydb.shared.models.RawMaterialProvider;
import com.appspot.milkydb.shared.models.Supply;

public class ManagerActionSet<LightDto extends Dto, FullDto extends Dto> {

	public static ManagerActionSet<LightEmployee, Employee> employee = new ManagerActionSet<LightEmployee, Employee>(
			"employee");

	public static ManagerActionSet<RawMaterialClass, BaseProductClass> rawMaterialClass = new ManagerActionSet<RawMaterialClass, BaseProductClass>(
			"rawMaterialClass");

	public static ManagerActionSet<FinalProductClass, BaseProductClass> finalProductClass = new ManagerActionSet<FinalProductClass, BaseProductClass>(
			"finalProductClass");

	public static ManagerActionSet<RawMaterialProvider, Partner> rawMaterialProvider = new ManagerActionSet<RawMaterialProvider, Partner>(
			"rawMaterialProvider");

	public static ManagerActionSet<FinalProductReseller, Partner> finalProductReseller = new ManagerActionSet<FinalProductReseller, Partner>(
			"finalProductReseller");

	public static ManagerActionSet<Supply, Supply> supply = new ManagerActionSet<Supply, Supply>(
			"supply");

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
