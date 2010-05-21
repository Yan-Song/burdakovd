package com.appspot.milkydb.client.presenter;

import java.util.ArrayList;
import java.util.List;

import com.appspot.milkydb.client.entityManagers.AbstractEntityManager.Events.AddEntityEvent;
import com.appspot.milkydb.client.entityManagers.AbstractEntityManager.Events.EditEntityEvent;
import com.appspot.milkydb.client.service.AsyncRequest;
import com.appspot.milkydb.client.service.ManagedAsyncService;
import com.appspot.milkydb.client.ui.Wait;
import com.appspot.milkydb.client.ui.Waitable;
import com.appspot.milkydb.shared.HasKey;
import com.appspot.milkydb.shared.dto.Dto;
import com.appspot.milkydb.shared.dto.DtoList;
import com.appspot.milkydb.shared.dto.EncodedKey;
import com.appspot.milkydb.shared.dto.EncodedKeys;
import com.appspot.milkydb.shared.dto.RpcVoid;
import com.appspot.milkydb.shared.service.action.Action;
import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.event.dom.client.HasClickHandlers;
import com.google.gwt.event.shared.HandlerManager;
import com.google.gwt.user.client.Window;
import com.google.gwt.user.client.rpc.AsyncCallback;
import com.google.gwt.user.client.ui.HasWidgets;
import com.google.gwt.user.client.ui.Widget;

public abstract class AbstractEntitiesTablePresenter<LightDto extends Dto & HasKey<EncodedKey>>
		implements Presenter {

	public interface Display<LightDto> {
		Widget asWidget();

		HasClickHandlers getAddButton();

		HasClickHandlers getDeleteButton();

		HasClickHandlers getEntitiesTable();

		HasClickHandlers getRefreshButton();

		int getRowForEvent(ClickEvent event);

		List<Integer> getSelectedRows();

		void setData(final List<LightDto> data);
	}

	private final Display<LightDto> display;
	private final ManagedAsyncService service;
	private final HandlerManager localEventBus;
	private final Waitable wait;
	private ArrayList<EncodedKey> keys;

	public AbstractEntitiesTablePresenter(final Display<LightDto> display,
			final ManagedAsyncService service,
			final HandlerManager localEventBus, final HandlerManager eventBus) {

		this.display = display;
		this.service = service;
		this.localEventBus = localEventBus;
		this.wait = new Wait(eventBus, service);

		bind();
	}

	private void bind() {
		display.getAddButton().addClickHandler(new ClickHandler() {
			@Override
			public void onClick(final ClickEvent event) {
				fireAddEntityEvent();
			}
		});

		display.getEntitiesTable().addClickHandler(new ClickHandler() {

			@Override
			public void onClick(final ClickEvent event) {
				onTableClick(event);
			}
		});

		display.getRefreshButton().addClickHandler(new ClickHandler() {
			@Override
			public void onClick(final ClickEvent event) {
				fetchEntities();
			}
		});

		display.getDeleteButton().addClickHandler(new ClickHandler() {
			@Override
			public void onClick(final ClickEvent event) {
				onDelete(display.getSelectedRows());
			}
		});
	}

	private AsyncRequest<EncodedKeys, RpcVoid> doDelete(
			final ArrayList<EncodedKey> selectedKeys) {
		return service.execute(provideDeleteAction(), new EncodedKeys(
				selectedKeys), new AsyncCallback<RpcVoid>() {
			@Override
			public void onFailure(final Throwable caught) {
				fetchEntities();
				Window.alert("Failed to delete");
			}

			@Override
			public void onSuccess(final RpcVoid result) {
				fetchEntities();
			}
		}, "Удаление");
	}

	private void fetchEntities() {
		wait.add(service.execute(provideGetAction(), null,
				new AsyncCallback<DtoList<LightDto>>() {

					@Override
					public void onFailure(final Throwable caught) {
						Window.alert("Can't fetch entities");
						caught.printStackTrace();
					}

					@Override
					public void onSuccess(final DtoList<LightDto> result) {
						keys = new ArrayList<EncodedKey>();
						for (final LightDto e : result) {
							keys.add(e.getKey());
						}
						display.setData(result);
					}
				}, "Получение списка"));
	}

	private void fireAddEntityEvent() {
		localEventBus.fireEvent(new AddEntityEvent());
	}

	private void fireEditEntityEvent(final EncodedKey encodedKey) {
		localEventBus.fireEvent(new EditEntityEvent(encodedKey));
	}

	@Override
	public void go(final HasWidgets container) {
		container.clear();
		container.add(display.asWidget());

		fetchEntities();
	}

	private void onDelete(final List<Integer> selectedRows) {
		if (selectedRows.isEmpty()) {
			Window.alert("Не выбрано ни одного элемента");
		} else if (Window.confirm("Вы действительно хотите удалить "
				+ selectedRows.size() + " элементов?")) {

			final ArrayList<EncodedKey> selectedKeys = new ArrayList<EncodedKey>();
			for (final Integer i : selectedRows) {
				selectedKeys.add(keys.get(i));
			}

			wait.add(doDelete(selectedKeys));
		}
	}

	private void onTableClick(final ClickEvent event) {
		final int idx = display.getRowForEvent(event);
		if (idx >= 0) {
			fireEditEntityEvent(keys.get(idx));
		}
	}

	protected abstract Action<EncodedKeys, RpcVoid> provideDeleteAction();

	protected abstract Action<RpcVoid, DtoList<LightDto>> provideGetAction();
}
