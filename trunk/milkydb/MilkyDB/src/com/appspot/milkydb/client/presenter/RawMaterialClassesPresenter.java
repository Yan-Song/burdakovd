package com.appspot.milkydb.client.presenter;

import com.appspot.milkydb.client.event.AddRawMaterialClassEvent;
import com.appspot.milkydb.client.event.EditRawMaterialClassEvent;
import com.appspot.milkydb.client.service.ManagedAsyncService;
import com.appspot.milkydb.shared.dto.DtoList;
import com.appspot.milkydb.shared.dto.EncodedKeys;
import com.appspot.milkydb.shared.dto.LightProductClass;
import com.appspot.milkydb.shared.dto.RpcVoid;
import com.appspot.milkydb.shared.service.Action;
import com.google.gwt.event.shared.HandlerManager;

public class RawMaterialClassesPresenter extends
		AbstractEntitiesTablePresenter<LightProductClass> {

	public interface Display extends
			AbstractEntitiesTablePresenter.Display<LightProductClass> {
	}

	public RawMaterialClassesPresenter(final Display display,
			final ManagedAsyncService service, final HandlerManager eventBus) {
		super(display, service, eventBus);
	}

	@Override
	protected void fireAddEntityEvent() {
		eventBus.fireEvent(new AddRawMaterialClassEvent());
	}

	@Override
	protected void fireEditEntityEvent(final String key) {
		eventBus.fireEvent(new EditRawMaterialClassEvent(key));
	}

	@Override
	protected Action<EncodedKeys, RpcVoid> provideDeleteAction() {
		return Action.deleteRawMaterialsClasses;
	}

	@Override
	protected Action<RpcVoid, DtoList<LightProductClass>> provideGetAction() {
		return Action.getRawMaterialsClasses;
	}

}
