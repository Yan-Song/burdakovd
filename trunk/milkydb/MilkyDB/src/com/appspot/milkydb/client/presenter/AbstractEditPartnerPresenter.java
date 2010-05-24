package com.appspot.milkydb.client.presenter;

import com.appspot.milkydb.client.service.ManagedAsyncService;
import com.appspot.milkydb.client.validation.ValidationError;
import com.appspot.milkydb.shared.dto.SingleKey;
import com.appspot.milkydb.shared.models.ContactInfo;
import com.appspot.milkydb.shared.models.Partner;
import com.google.gwt.event.shared.HandlerManager;
import com.google.gwt.user.client.ui.HasValue;

public abstract class AbstractEditPartnerPresenter extends
		AbstractEditEntityPresenter<Partner> {

	public interface Display extends AbstractEditEntityPresenter.Display {
		HasValue<String> getAddress();

		HasValue<String> getName();

		HasValue<String> getPhoneNumber();
	}

	private final Display display;

	/**
	 * @param display
	 * @param service
	 * @param localEventBus
	 * @param eventBus
	 */
	public AbstractEditPartnerPresenter(final Display display,
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
	public AbstractEditPartnerPresenter(final Display display,
			final ManagedAsyncService service,
			final HandlerManager localEventBus, final HandlerManager eventBus,
			final SingleKey key) {
		super(display, service, localEventBus, eventBus, key);
		this.display = display;
	}

	@Override
	protected void displayDto(final Partner data) {
		display.getAddress().setValue(data.getContactInfo().getAddress());
		display.getPhoneNumber().setValue(
				data.getContactInfo().getPhoneNumber());
		display.getName().setValue(data.getName());
	}

	@Override
	protected Partner makeDto() throws ValidationError {
		return new Partner(display.getName().getValue(), new ContactInfo(
				display.getAddress().getValue(), display.getPhoneNumber()
						.getValue()));
	}
}
