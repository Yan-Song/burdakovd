package com.appspot.milkydb.client.presenter;

import java.io.Serializable;

import com.appspot.milkydb.client.service.ManagedAsyncService;
import com.appspot.milkydb.client.ui.Wait;
import com.appspot.milkydb.client.validation.CanDisplayValidationErrors;
import com.appspot.milkydb.client.validation.ValidationError;
import com.appspot.milkydb.client.view.Waitable;
import com.appspot.milkydb.shared.dto.HasKey;
import com.appspot.milkydb.shared.dto.Validatable;
import com.appspot.milkydb.shared.service.Action;
import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.event.dom.client.HasClickHandlers;
import com.google.gwt.event.shared.HandlerManager;
import com.google.gwt.user.client.Window;
import com.google.gwt.user.client.rpc.AsyncCallback;
import com.google.gwt.user.client.ui.HasWidgets;
import com.google.gwt.user.client.ui.Widget;

public abstract class AbstractEditPresenter<Dto extends HasKey<String> & Serializable & Validatable>
		implements Presenter {

	public interface Display extends CanDisplayValidationErrors {
		Widget asWidget();

		HasClickHandlers getCancelButton();

		HasClickHandlers getSubmitButton();
	}

	protected final Waitable wait;
	private final Display display;
	protected final ManagedAsyncService service;
	protected final HandlerManager eventBus;
	protected final String key;

	public AbstractEditPresenter(final Display display,
			final ManagedAsyncService service, final HandlerManager eventBus) {
		this(display, service, eventBus, null);
	}

	public AbstractEditPresenter(final Display display,
			final ManagedAsyncService service, final HandlerManager eventBus,
			final String key) {
		this.display = display;
		this.service = service;
		this.eventBus = eventBus;
		this.key = key;
		this.wait = new Wait(eventBus, service);
	}

	private void bind() {
		display.getCancelButton().addClickHandler(new ClickHandler() {
			@Override
			public void onClick(final ClickEvent event) {
				fireEditFinishedEvent();
			}
		});

		display.getSubmitButton().addClickHandler(new ClickHandler() {
			@Override
			public void onClick(final ClickEvent event) {
				onSubmit();
			}
		});
	}

	protected abstract void displayDto(final Dto data);

	private void doSave(final Dto dto) throws ValidationError {
		wait.add(service.execute(provideSaveEntityAction(), dto,
				new AsyncCallback<String>() {
					@Override
					public void onFailure(final Throwable caught) {
						if (caught instanceof ValidationError) {
							display
									.showValidationError((ValidationError) caught);
						} else {
							Window.alert("Failed to save");
							caught.printStackTrace();
						}
					}

					@Override
					public void onSuccess(final String result) {
						fireEditFinishedEvent();
					}
				}, "Сохранение"));
	}

	private void fetchEntityDetails() {
		wait.add(service.execute(provideGetEntityAction(), key,
				new AsyncCallback<Dto>() {

					@Override
					public void onFailure(final Throwable caught) {
						Window.alert("Can't fetch entity");
						caught.printStackTrace();
					}

					@Override
					public void onSuccess(final Dto result) {
						displayDto(result);
					}
				}, "Загрузка объекта"));
	}

	protected abstract void fireEditFinishedEvent();

	@Override
	public void go(final HasWidgets container) {
		bind();

		container.clear();
		container.add(display.asWidget());

		if (key != null) {
			fetchEntityDetails();
		}
	}

	protected abstract Dto makeDto() throws ValidationError;

	private void onSubmit() {
		display.clearErrors();

		try {
			final Dto dto = makeDto();
			dto.validate();
			doSave(dto);
		} catch (final ValidationError e) {
			display.showValidationError(e);
		}
	}

	protected abstract Action<String, Dto> provideGetEntityAction();

	protected abstract Action<Dto, String> provideSaveEntityAction();
}