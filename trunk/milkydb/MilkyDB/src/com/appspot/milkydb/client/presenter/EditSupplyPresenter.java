/**
 * 
 */
package com.appspot.milkydb.client.presenter;

import java.util.ArrayList;

import com.appspot.milkydb.client.service.ManagedAsyncService;
import com.appspot.milkydb.client.ui.FreeListBox;
import com.appspot.milkydb.client.validation.ValidationError;
import com.appspot.milkydb.shared.dto.DtoList;
import com.appspot.milkydb.shared.dto.SingleKey;
import com.appspot.milkydb.shared.models.RawMaterialClass;
import com.appspot.milkydb.shared.models.Supply;
import com.appspot.milkydb.shared.service.action.Action;
import com.appspot.milkydb.shared.service.action.ManagerActionSet;
import com.google.gwt.event.shared.HandlerManager;
import com.google.gwt.user.client.Window;
import com.google.gwt.user.client.rpc.AsyncCallback;
import com.google.gwt.user.client.ui.HasWidgets;
import com.googlecode.objectify.Key;

/**
 * @author burdakovd
 * 
 */
public class EditSupplyPresenter extends AbstractEditContractPresenter<Supply> {

	public interface Display extends AbstractEditContractPresenter.Display {
		FreeListBox getRawMaterial();

		FreeListBox getRawMaterialProvider();
	}

	private final Display display;
	private Supply data;
	private ArrayList<Key<RawMaterialClass>> materialKeys;
	private ArrayList<String> materialNames;

	/**
	 * @param display
	 * @param service
	 * @param localEventBus
	 * @param eventBus
	 */
	public EditSupplyPresenter(final Display display,
			final ManagedAsyncService service,
			final HandlerManager localEventBus, final HandlerManager eventBus) {
		this(display, service, localEventBus, eventBus, null);
	}

	/**
	 * @param display
	 * @param service
	 * @param localEventBus
	 * @param eventBus
	 * @param key
	 */
	public EditSupplyPresenter(final Display display,
			final ManagedAsyncService service,
			final HandlerManager localEventBus, final HandlerManager eventBus,
			final SingleKey key) {
		super(display, service, localEventBus, eventBus, key);
		this.display = display;
	}

	/**
	 * 
	 */
	private void displayData() {
		// TODO Auto-generated method stub

	}

	@Override
	protected void displayDto(final Supply data) {
		this.data = data;
		displayData();
	}

	@Override
	public void go(final HasWidgets container) {
		super.go(container);
		wait.add(service.execute(ManagerActionSet.rawMaterialClass
				.provideGetAllAction(), null,
				new AsyncCallback<DtoList<RawMaterialClass>>() {

					@Override
					public void onFailure(final Throwable caught) {
						Window.alert(caught.getLocalizedMessage());
					}

					@Override
					public void onSuccess(final DtoList<RawMaterialClass> result) {
						processRawMaterialClassList(result);
					}
				}));
	}

	@Override
	protected Supply makeDto() throws ValidationError {
		return null;
	}

	/**
	 * @param result
	 */
	protected void processRawMaterialClassList(
			final DtoList<RawMaterialClass> result) {
		materialKeys = new ArrayList<Key<RawMaterialClass>>();
		materialNames = new ArrayList<String>();
		for (final RawMaterialClass clas : result) {
			materialNames.add(clas.getName());
			// materialKeys.add(new Key<RawMaterialClass>());
		}
	}

	@Override
	protected Action<SingleKey, Supply> provideGetEntityAction() {
		return ManagerActionSet.supply.provideGetAction();
	}

	@Override
	protected Action<Supply, SingleKey> provideSaveEntityAction() {
		return ManagerActionSet.supply.provideSaveAction();
	}

}
