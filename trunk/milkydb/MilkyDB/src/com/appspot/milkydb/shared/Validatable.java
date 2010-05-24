package com.appspot.milkydb.shared;

import com.appspot.milkydb.client.validation.ValidationError;

/*
 * DTO, который можно проверить на корректность его полей.
 * Проверка возможна и на клиентской стороне, и на серверной
 * 
 * Реализующие этот интерфейс классы также должны предоставить enum Fields с списком полей,
 * которые потом будут использоваться для конструирования ValidationError 
 */
public interface Validatable {

	public enum Delete implements Fields {
		canNotDelete
	}

	public interface Fields {
	}

	/*
	 * должны выбрасывать исключения только для полей, определённых в Fields
	 */
	void validate() throws ValidationError;
}
