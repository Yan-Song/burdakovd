package com.appspot.milkydb.client.entityManagers;

import com.appspot.milkydb.client.entityManagers.AbstractEntityManager.Events.AddEntityEvent;
import com.appspot.milkydb.client.entityManagers.AbstractEntityManager.Events.AddEntityEventHandler;
import com.appspot.milkydb.client.entityManagers.AbstractEntityManager.Events.EditEntityEvent;
import com.appspot.milkydb.client.entityManagers.AbstractEntityManager.Events.EditEntityEventHandler;
import com.appspot.milkydb.client.entityManagers.AbstractEntityManager.Events.EditEntityFinishedEvent;
import com.appspot.milkydb.client.entityManagers.AbstractEntityManager.Events.EditEntityFinishedEventHandler;
import com.appspot.milkydb.client.presenter.Presenter;
import com.appspot.milkydb.shared.dto.SingleKey;
import com.google.gwt.event.shared.EventHandler;
import com.google.gwt.event.shared.GwtEvent;
import com.google.gwt.event.shared.HandlerManager;
import com.google.gwt.user.client.History;

/*
 * Абстрактный базовый класс для управления какими-либо сущностями
 */
public abstract class AbstractEntityManager {

	public static class Events {
		public static class AddEntityEvent extends
				GwtEvent<AddEntityEventHandler> {
			public static final Type<AddEntityEventHandler> TYPE = new Type<AddEntityEventHandler>();

			@Override
			protected void dispatch(final AddEntityEventHandler handler) {
				handler.onAddEntity(this);
			}

			@Override
			public com.google.gwt.event.shared.GwtEvent.Type<AddEntityEventHandler> getAssociatedType() {
				return TYPE;
			}
		}

		public interface AddEntityEventHandler extends EventHandler {

			public void onAddEntity(final AddEntityEvent addEntityEvent);

		}

		public static class EditEntityEvent extends
				GwtEvent<EditEntityEventHandler> {
			public static final Type<EditEntityEventHandler> TYPE = new Type<EditEntityEventHandler>();

			private final SingleKey key;

			public EditEntityEvent(final SingleKey key) {
				this.key = key;
			}

			@Override
			protected void dispatch(final EditEntityEventHandler handler) {
				handler.onEditEntity(this);
			}

			@Override
			public com.google.gwt.event.shared.GwtEvent.Type<EditEntityEventHandler> getAssociatedType() {
				return TYPE;
			}

			public SingleKey getKey() {
				return key;
			}
		}

		public interface EditEntityEventHandler extends EventHandler {

			public void onEditEntity(final EditEntityEvent editEntityEvent);

		}

		public static class EditEntityFinishedEvent extends
				GwtEvent<EditEntityFinishedEventHandler> {
			public static final Type<EditEntityFinishedEventHandler> TYPE = new Type<EditEntityFinishedEventHandler>();

			@Override
			protected void dispatch(final EditEntityFinishedEventHandler handler) {
				handler.onEditEntityFinished(this);
			}

			@Override
			public com.google.gwt.event.shared.GwtEvent.Type<EditEntityFinishedEventHandler> getAssociatedType() {
				return TYPE;
			}
		}

		public interface EditEntityFinishedEventHandler extends EventHandler {

			void onEditEntityFinished(
					EditEntityFinishedEvent editEntityFinishedEvent);

		}
	}

	private final String baseUrl;
	private final HandlerManager localEventBus;

	public AbstractEntityManager(final String baseUrl) {
		this.baseUrl = baseUrl;
		this.localEventBus = new HandlerManager(this);

		bind();
	}

	private void bind() {
		localEventBus.addHandler(EditEntityEvent.TYPE,
				new EditEntityEventHandler() {
					@Override
					public void onEditEntity(
							final EditEntityEvent editEntityEvent) {
						goToEdit(editEntityEvent.getKey());
					}
				});

		localEventBus.addHandler(AddEntityEvent.TYPE,
				new AddEntityEventHandler() {
					@Override
					public void onAddEntity(final AddEntityEvent addEntityEvent) {
						goToAdd();
					}
				});

		localEventBus.addHandler(EditEntityFinishedEvent.TYPE,
				new EditEntityFinishedEventHandler() {
					@Override
					public void onEditEntityFinished(
							final EditEntityFinishedEvent editEntityFinishedEvent) {
						goToList();
					}
				});
	}

	public String getBaseUrl() {
		return baseUrl;
	}

	protected abstract Presenter getEditPresenter(SingleKey key);

	private String getEditUrl(final SingleKey key) {
		return getEditUrlPrefix() + key.getValue();
	}

	private String getEditUrlPrefix() {
		return getBaseUrl() + "/edit/";
	}

	protected abstract Presenter getListPresenter();

	protected HandlerManager getLocalEventBus() {
		return localEventBus;
	}

	protected abstract Presenter getNewPresenter();

	private String getNewUrl() {
		return getBaseUrl() + "/new";
	}

	public Presenter getPresenter(final String token) {
		Presenter presenter = null;

		if (token.equals(getBaseUrl())) {
			presenter = getListPresenter();
		} else if (token.equals(getNewUrl())) {
			presenter = getNewPresenter();
		} else if (token.startsWith(getEditUrlPrefix())) {
			presenter = getEditPresenter(new SingleKey(Long.parseLong(token
					.substring(getEditUrlPrefix().length()))));
		}

		return presenter;
	}

	private void goToAdd() {
		History.newItem(getNewUrl());
	}

	private void goToEdit(final SingleKey key) {
		History.newItem(getEditUrl(key));
	}

	private void goToList() {
		History.newItem(getBaseUrl());
	}
}
