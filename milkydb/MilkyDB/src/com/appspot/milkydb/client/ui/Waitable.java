package com.appspot.milkydb.client.ui;

import com.appspot.milkydb.client.service.AsyncRequest;

/*
 * интерфейс, способный выдавать модальную табличку типа "Подождите" и убирать её
 */
public interface Waitable {
	public void add(final AsyncRequest<?, ?> request);

	public void clear();
}
