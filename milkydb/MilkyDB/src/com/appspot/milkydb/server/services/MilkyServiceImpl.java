package com.appspot.milkydb.server.services;

import java.util.HashMap;

import com.appspot.milkydb.client.validation.ValidationError;
import com.appspot.milkydb.shared.dto.Dto;
import com.appspot.milkydb.shared.dto.DtoList;
import com.appspot.milkydb.shared.dto.EncodedKey;
import com.appspot.milkydb.shared.dto.EncodedKeys;
import com.appspot.milkydb.shared.dto.RpcRequest;
import com.appspot.milkydb.shared.dto.RpcResponse;
import com.appspot.milkydb.shared.dto.RpcVoid;
import com.appspot.milkydb.shared.service.MilkyService;
import com.appspot.milkydb.shared.service.action.Action;
import com.appspot.milkydb.shared.service.action.ManagerActionSet;
import com.google.gwt.user.server.rpc.RemoteServiceServlet;

@SuppressWarnings("serial")
public class MilkyServiceImpl extends RemoteServiceServlet implements
		MilkyService {

	/*
	 * соответствие между командами и их обработчиками
	 */
	private final HashMap<Action<?, ?>, ActionHandler<?, ?>> handlers = new HashMap<Action<?, ?>, ActionHandler<?, ?>>();

	public MilkyServiceImpl() {
		registerActionHandler(Action.getAppointments,
				new GetAppointmentsHandler());

		registerManagerActionSetHandlers(ManagerActionSet.Employee,
				new DeleteEmployeeHandler(), new GetEmployeeHandler(),
				new GetEmployeesHandler(), new SaveEmployeeHandler());

		registerManagerActionSetHandlers(ManagerActionSet.RawMaterialClass,
				new DeleteRawMaterialClassHandler(),
				new GetRawMaterialClassHandler(),
				new GetRawMaterialClassesHandler(),
				new SaveRawMaterialClassHandler());

		registerManagerActionSetHandlers(ManagerActionSet.FinalProductClass,
				new DeleteFinalProductClassHandler(),
				new GetFinalProductClassHandler(),
				new GetFinalProductClassesHandler(),
				new SaveFinalProductClassHandler());
	}

	@SuppressWarnings("unchecked")
	@Override
	/*
	 * Каст внутри не должен давать ошибок, так как в handlers хранятся только
	 * совпадающие по параметрам команды и их обработчики. Несовпадающие там
	 * оказаться не могут, так как handlers имеет модификатор private, а метод
	 * RegisterActionHandler параметризован
	 */
	public <Req extends RpcRequest, Resp extends RpcResponse> Resp execute(
			final Action<Req, Resp> action, final Req request)
			throws ValidationError {

		final ActionHandler<Req, Resp> handler = (ActionHandler<Req, Resp>) handlers
				.get(action);

		if (handler == null) {
			throw new NullPointerException("Handler for action " + action
					+ " not registered");
		} else {
			return handler.execute(request);
		}
	}

	private <Req extends RpcRequest, Resp extends RpcResponse> void registerActionHandler(
			final Action<Req, Resp> action,
			final ActionHandler<Req, Resp> handler) {

		handlers.put(action, handler);
	}

	private <LightDto extends Dto, FullDto extends Dto> void registerManagerActionSetHandlers(
			final ManagerActionSet<LightDto, FullDto> set,
			final ActionHandler<EncodedKeys, RpcVoid> delete,
			final ActionHandler<EncodedKey, FullDto> get,
			final ActionHandler<RpcVoid, DtoList<LightDto>> getAll,
			final ActionHandler<FullDto, EncodedKey> save) {

		registerActionHandler(set.provideDeleteAction(), delete);
		registerActionHandler(set.provideGetAction(), get);
		registerActionHandler(set.provideGetAllAction(), getAll);
		registerActionHandler(set.provideSaveAction(), save);
	}
}
