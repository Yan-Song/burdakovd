package com.appspot.milkydb.shared.service;

import com.appspot.milkydb.shared.dto.Dto;
import com.appspot.milkydb.shared.dto.DtoList;
import com.appspot.milkydb.shared.dto.EncodedKey;
import com.appspot.milkydb.shared.dto.EncodedKeys;
import com.appspot.milkydb.shared.dto.FullEmployee;
import com.appspot.milkydb.shared.dto.LightAppointment;
import com.appspot.milkydb.shared.dto.LightEmployee;
import com.appspot.milkydb.shared.dto.LightProductClass;
import com.appspot.milkydb.shared.dto.RpcRequest;
import com.appspot.milkydb.shared.dto.RpcResponse;
import com.appspot.milkydb.shared.dto.RpcVoid;

/*
 * Нужно различать различные команды, и пользоваться оператором == нельзя,
 * так как может прийти другой экземпляр той же команды по RPC.
 * 
 * Пришлось для их различия сделать строковое имя, которое должно быть разным для разных команд.
 * 
 * Поэтому делаю конструктор приватным, и получать доступ к экземлярам команд можно только с помощью
 * статических полей этого класса, за которыми будет несложно уследить, чтобы не было коллизий имён.
 * 
 */
@SuppressWarnings("serial")
public class Action<Req extends RpcRequest, Resp extends RpcResponse>
		implements Dto {

	private String name;

	public static final Action<RpcVoid, DtoList<LightAppointment>> getAppointments = new Action<RpcVoid, DtoList<LightAppointment>>(
			"getAppointments");

	public static final Action<RpcVoid, DtoList<LightEmployee>> getLightEmployeeList = new Action<RpcVoid, DtoList<LightEmployee>>(
			"getLightEmployeeList");

	public static final Action<EncodedKey, FullEmployee> getEmployee = new Action<EncodedKey, FullEmployee>(
			"getEmployee");

	public static final Action<FullEmployee, EncodedKey> saveEmployee = new Action<FullEmployee, EncodedKey>(
			"saveEmployee");

	public static final Action<EncodedKeys, RpcVoid> deleteEmployee = new Action<EncodedKeys, RpcVoid>(
			"deleteEmployee");

	public static final Action<RpcVoid, DtoList<LightProductClass>> getRawMaterialsClasses = new Action<RpcVoid, DtoList<LightProductClass>>(
			"getRawMaterialsClasses");

	public static final Action<EncodedKeys, RpcVoid> deleteRawMaterialsClasses = new Action<EncodedKeys, RpcVoid>(
			"deleteRawMaterialClasses");

	/*
	 * для GWT-RPC
	 */
	private Action() {
	}

	private Action(final String name) {
		this.setName(name);
	}

	@Override
	public boolean equals(final Object obj) {
		if (this == obj) {
			return true;
		}
		if (obj == null) {
			return false;
		}
		if (getClass() != obj.getClass()) {
			return false;
		}
		final Action<?, ?> other = (Action<?, ?>) obj;
		if (getName() == null) {
			if (other.getName() != null) {
				return false;
			}
		} else if (!getName().equals(other.getName())) {
			return false;
		}
		return true;
	}

	public String getName() {
		return name;
	}

	@Override
	public int hashCode() {
		return getName().hashCode();
	}

	private void setName(final String name) {
		this.name = name;
	}

	@Override
	public String toString() {
		return getClass().getName() + '@' + getName();
	}
}
