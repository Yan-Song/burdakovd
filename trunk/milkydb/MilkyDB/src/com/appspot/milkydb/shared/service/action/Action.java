package com.appspot.milkydb.shared.service.action;

import com.appspot.milkydb.shared.dto.Dto;
import com.appspot.milkydb.shared.dto.DtoList;
import com.appspot.milkydb.shared.dto.RpcRequest;
import com.appspot.milkydb.shared.dto.RpcResponse;
import com.appspot.milkydb.shared.dto.RpcVoid;
import com.appspot.milkydb.shared.models.Appointment;

/*
 * Нужно различать различные команды, и пользоваться оператором == нельзя,
 * так как может прийти другой экземпляр той же команды по RPC.
 * 
 * Пришлось для их различия сделать строковое имя, которое должно быть разным для разных команд.
 * 
 * Поэтому делаю конструктор пакетной видимости, и получать доступ к экземлярам команд можно только с помощью
 * статических полей этого класса, и классов этого пакета за которыми будет несложно уследить, чтобы не было коллизий имён.
 * 
 */
@SuppressWarnings("serial")
public class Action<Req extends RpcRequest, Resp extends RpcResponse>
		implements Dto {

	private String name;

	public static final Action<RpcVoid, DtoList<Appointment>> getAppointments = new Action<RpcVoid, DtoList<Appointment>>(
			"getAppointments");

	/*
	 * для GWT-RPC
	 */
	@SuppressWarnings("unused")
	private Action() {
	}

	Action(final String name) {
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
