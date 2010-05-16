package com.appspot.milkydb.client.view;

/*
 * интерфейс, способный выдавать модальную табличку типа "Подождите" и убирать её
 */
public interface Waitable {
	void startWait(String text);

	void stopWait();
}
