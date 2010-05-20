package com.appspot.milkydb.shared.dto;

import com.appspot.milkydb.client.validation.ValidationError;

/*
 * DTO, который можно проверить на корректность его полей.
 * Проверка возможна и на клиентской стороне, и на серверной
 * 
 * Реализующие этот интерфейс классы также должны предоставить интерфейс Fields с списком полей,
 * которые потом будут использоваться для конструирования ValidationError 
 */
public interface Validatable {

	/*
	 * должны содержать набор static final String, различных
	 */
	public interface Fields {
	}

	/*
	 * должны выбрасывать исключения только для полей, определённых в Fields
	 */
	void validate() throws ValidationError;
}
