package com.appspot.milkydb.shared.services;

import java.io.Serializable;
import java.util.ArrayList;

import com.appspot.milkydb.shared.dto.FullEmployee;
import com.appspot.milkydb.shared.dto.LightEmployee;
import com.appspot.milkydb.shared.dto.SerializableVoid;

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
public class Action<Req extends Serializable, Resp extends Serializable>
		implements Serializable {

	private String name;

	public static final Action<SerializableVoid, ArrayList<LightEmployee>> getLightEmployeeList = new Action<SerializableVoid, ArrayList<LightEmployee>>(
			"getLightEmployeeList");

	public static final Action<String, FullEmployee> getEmployee = new Action<String, FullEmployee>(
			"GetEmployeeHandler");

	public static final Action<FullEmployee, String> saveEmployee = new Action<FullEmployee, String>(
			"saveEmployee");

	public static final Action<SerializableVoid, ArrayList<String>> getAppointments = new Action<SerializableVoid, ArrayList<String>>(
			"GetAppointmentsHandler");

	/*
	 * для GWT-RPC
	 */
	private Action() {
	}

	private Action(final String name) {
		this.name = name;
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
		if (name == null) {
			if (other.name != null) {
				return false;
			}
		} else if (!name.equals(other.name)) {
			return false;
		}
		return true;
	}

	@Override
	public int hashCode() {
		return name.hashCode();
	}

	@Override
	public String toString() {
		return getClass().getName() + '@' + name;
	}
}
