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
import com.appspot.milkydb.shared.dto.KeyList;
import com.appspot.milkydb.shared.dto.RpcVoid;
import com.appspot.milkydb.shared.dto.SingleKey;
import com.appspot.milkydb.shared.service.action.Action;
import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.event.dom.client.HasClickHandlers;
import com.google.gwt.event.shared.HandlerManager;
import com.google.gwt.user.client.Window;
import com.google.gwt.user.client.rpc.AsyncCallback;
import com.google.gwt.user.client.ui.HasWidgets;
import com.google.gwt.user.client.ui.Widget;

public abstract class AbstractEntitiesTablePresenter<LightDto extends Dto & HasKey<Long>>
		implements Presenter {

	public interface Display<LightDto> {
		Widget asWidget();

		HasClickHandlers getAddButton();

		HasClickHandlers getDeleteButton();

		HasClickHandlers getEntitiesTable();

		HasClickHandlers getRefreshButton();

		int getRowForEvent(ClickEvent event);

		List<Integer> getSelectedRows();

		void setData(final List<? extends LightDto> data);
	}

	private final Display<? super LightDto> display;
	private final ManagedAsyncService service;
	private final HandlerManager localEventBus;
	private final Waitable wait;
	private ArrayList<SingleKey> keys;

	public AbstractEntitiesTablePresenter(
			final Display<? super LightDto> display,
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

	private AsyncRequest<KeyList, RpcVoid> doDelete(
			final ArrayList<SingleKey> selectedKeys) {
		return service.execute(provideDeleteAction(),
				new KeyList(selectedKeys), new AsyncCallback<RpcVoid>() {
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
						keys = new ArrayList<SingleKey>();
						for (final LightDto e : result) {
							keys.add(new SingleKey(e.getKey()));
						}
						display.setData(result);
					}
				}, "Получение списка"));
	}

	private void fireAddEntityEvent() {
		localEventBus.fireEvent(new AddEntityEvent());
	}

	private void fireEditEntityEvent(final SingleKey singleKey) {
		localEventBus.fireEvent(new EditEntityEvent(singleKey));
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

			final ArrayList<SingleKey> selectedKeys = new ArrayList<SingleKey>();
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

	protected abstract Action<KeyList, RpcVoid> provideDeleteAction();

	protected abstract Action<RpcVoid, DtoList<LightDto>> provideGetAction();
}
