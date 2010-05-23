package com.appspot.milkydb.server.services;

import java.util.HashMap;

import com.appspot.milkydb.client.validation.ValidationError;
import com.appspot.milkydb.shared.dto.Dto;
import com.appspot.milkydb.shared.dto.DtoList;
import com.appspot.milkydb.shared.dto.KeyList;
import com.appspot.milkydb.shared.dto.RpcRequest;
import com.appspot.milkydb.shared.dto.RpcResponse;
import com.appspot.milkydb.shared.dto.RpcVoid;
import com.appspot.milkydb.shared.dto.SingleKey;
import com.appspot.milkydb.shared.models.Appointment;
import com.appspot.milkydb.shared.models.Employee;
import com.appspot.milkydb.shared.models.Ferment;
import com.appspot.milkydb.shared.models.FinalProductClass;
import com.appspot.milkydb.shared.models.MicroElement;
import com.appspot.milkydb.shared.models.RawMaterialClass;
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
				new SimpleGetAllEntitiesHandler<Appointment>(Appointment.class,
						"name"));

		registerManagerActionSetHandlers(ManagerActionSet.Employee,
				new SimpleDeleteEntitiesHandler<Employee>(Employee.class),
				new SimpleGetEntityHandler<Employee>(Employee.class),
				new GetEmployeesHandler(), new SaveEmployeeHandler());

		registerManagerActionSetHandlers(ManagerActionSet.RawMaterialClass,
				new SimpleDeleteEntitiesHandler<RawMaterialClass>(
						RawMaterialClass.class),
				new SimpleGetEntityHandler<RawMaterialClass>(
						RawMaterialClass.class),
				new GetProductClassesHandler<RawMaterialClass>(
						RawMaterialClass.class),
				new SaveProductClassHandler<RawMaterialClass>(
						RawMaterialClass.class));

		registerManagerActionSetHandlers(ManagerActionSet.FinalProductClass,
				new SimpleDeleteEntitiesHandler<FinalProductClass>(
						FinalProductClass.class),
				new SimpleGetEntityHandler<FinalProductClass>(
						FinalProductClass.class),
				new GetProductClassesHandler<FinalProductClass>(
						FinalProductClass.class),
				new SaveProductClassHandler<FinalProductClass>(
						FinalProductClass.class));

		registerActionHandler(Action.getFerments,
				new SimpleGetAllEntitiesHandler<Ferment>(Ferment.class, "name"));

		registerActionHandler(Action.getMicroElements,
				new SimpleGetAllEntitiesHandler<MicroElement>(
						MicroElement.class, "name"));
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
			final ActionHandler<Req, ? extends Resp> handler) {

		handlers.put(action, handler);
	}

	private <LightDto extends Dto, FullDto extends Dto> void registerManagerActionSetHandlers(
			final ManagerActionSet<LightDto, FullDto> set,
			final ActionHandler<KeyList, RpcVoid> delete,
			final ActionHandler<SingleKey, ? extends FullDto> get,
			final ActionHandler<RpcVoid, DtoList<LightDto>> getAll,
			final ActionHandler<FullDto, SingleKey> save) {

		registerActionHandler(set.provideDeleteAction(), delete);
		registerActionHandler(set.provideGetAction(), get);
		registerActionHandler(set.provideGetAllAction(), getAll);
		registerActionHandler(set.provideSaveAction(), save);
	}
}
