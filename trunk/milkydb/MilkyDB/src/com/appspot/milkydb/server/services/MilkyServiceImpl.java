package com.appspot.milkydb.server.services;

import java.io.Serializable;
import java.util.HashMap;

import com.appspot.milkydb.shared.services.Action;
import com.appspot.milkydb.shared.services.MilkyService;
import com.google.gwt.user.server.rpc.RemoteServiceServlet;

@SuppressWarnings("serial")
public class MilkyServiceImpl extends RemoteServiceServlet implements
		MilkyService {

	/*
	 * соответствие между командами и их обработчиками
	 */
	private final HashMap<Action<?, ?>, ActionHandler<?, ?>> handlers = new HashMap<Action<?, ?>, ActionHandler<?, ?>>();

	public MilkyServiceImpl() {
		registerActionHandler(Action.getLightEmployeeList,
				new GetLightEmployeeListHandler());
		registerActionHandler(Action.getEmployee, new GetEmployeeHandler());
		registerActionHandler(Action.saveEmployee, new SaveEmployeeHandler());
		registerActionHandler(Action.getAppointments,
				new GetAppointmentsHandler());
	}

	@SuppressWarnings("unchecked")
	@Override
	/*
	 * Каст внутри не должен давать ошибок, так как в handlers хранятся только
	 * совпадающие по параметрам команды и их обработчики. Несовпадающие там
	 * оказаться не могут, так как handlers имеет модификатор private, а метод
	 * RegisterActionHandler параметризован
	 */
	public <Req extends Serializable, Resp extends Serializable> Resp execute(
			final Action<Req, Resp> action, final Req request) {

		final ActionHandler<Req, Resp> handler = (ActionHandler<Req, Resp>) handlers
				.get(action);

		if (handler == null) {
			throw new NullPointerException("Handler for action " + action
					+ " not registered");
		} else {
			return handler.execute(request);
		}
	}

	private <Req extends Serializable, Resp extends Serializable> void registerActionHandler(
			final Action<Req, Resp> action,
			final ActionHandler<Req, Resp> handler) {

		handlers.put(action, handler);
	}
}
