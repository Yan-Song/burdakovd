package com.appspot.milkydb.client.presenter;

import com.appspot.milkydb.client.service.ManagedAsyncService;
import com.appspot.milkydb.shared.dto.DtoList;
import com.appspot.milkydb.shared.dto.EncodedKeys;
import com.appspot.milkydb.shared.dto.LightProductClass;
import com.appspot.milkydb.shared.dto.RpcVoid;
import com.appspot.milkydb.shared.service.action.Action;
import com.appspot.milkydb.shared.service.action.ManagerActionSet;
import com.google.gwt.event.shared.HandlerManager;

public class FinalProductClassPresenter extends
		AbstractEntitiesTablePresenter<LightProductClass> {

	public interface Display extends
			AbstractEntitiesTablePresenter.Display<LightProductClass> {
	}

	public FinalProductClassPresenter(final Display display,
			final ManagedAsyncService service,
			final HandlerManager localEventBus, final HandlerManager eventBus) {
		super(display, service, localEventBus, eventBus);
	}

	@Override
	protected Action<EncodedKeys, RpcVoid> provideDeleteAction() {
		return ManagerActionSet.FinalProductClass.provideDeleteAction();
	}

	@Override
	protected Action<RpcVoid, DtoList<LightProductClass>> provideGetAction() {
		return ManagerActionSet.FinalProductClass.provideGetAllAction();
	}

}
