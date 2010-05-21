package com.appspot.milkydb.client.presenter;

import com.appspot.milkydb.client.service.ManagedAsyncService;
import com.appspot.milkydb.client.ui.FreeMultiListBox;
import com.appspot.milkydb.client.validation.ValidationError;
import com.appspot.milkydb.shared.dto.EncodedKey;
import com.appspot.milkydb.shared.dto.FullProductClass;
import com.appspot.milkydb.shared.dto.TimeSpan;
import com.google.gwt.event.shared.HandlerManager;
import com.google.gwt.user.client.ui.HasValue;

public abstract class AbstractEditProductClassPresenter extends
		AbstractEditPresenter<FullProductClass> {

	public interface Display extends AbstractEditPresenter.Display {
		HasValue<String> getCalorificValue();

		HasValue<String> getFatness();

		FreeMultiListBox getFerments();

		FreeMultiListBox getMicroElements();

		HasValue<String> getName();

		HasValue<String> getPacking();

		HasValue<String> getStorageConstraints();

		HasValue<TimeSpan> getStorageLife();

		HasValue<String> getTransportationConstraints();
	}

	private final Display display;

	public AbstractEditProductClassPresenter(final Display display,
			final ManagedAsyncService service,
			final HandlerManager localEventBus, final HandlerManager eventBus) {
		this(display, service, localEventBus, eventBus, null);
	}

	public AbstractEditProductClassPresenter(final Display display,
			final ManagedAsyncService service,
			final HandlerManager localEventBus, final HandlerManager eventBus,
			final EncodedKey key) {
		super(display, service, localEventBus, eventBus, key);
		this.display = display;
	}

	@Override
	protected void displayDto(final FullProductClass data) {
		display.getName().setValue(data.getName());
		display.getFatness().setValue(data.getFatness().toString());
		display.getCalorificValue().setValue(
				data.getCalorificValue().toString());
		display.getStorageLife().setValue(data.getStorageLife());
		display.getStorageConstraints().setValue(data.getStorageConstraints());
		display.getTransportationConstraints().setValue(
				data.getTransportationConstraints());
		display.getPacking().setValue(data.getPacking());
		display.getFerments().setValue(data.getFerments());
		display.getMicroElements().setValue(data.getMicroElements());
	}

	@Override
	protected FullProductClass makeDto() throws ValidationError {
		return new FullProductClass(key, display.getName().getValue(),
				parseFloat(FullProductClass.Fields.fatness, display
						.getFatness().getValue()), parseFloat(
						FullProductClass.Fields.calorificValue, display
								.getCalorificValue().getValue()), display
						.getStorageLife().getValue(), display.getPacking()
						.getValue(),
				display.getStorageConstraints().getValue(), display
						.getTransportationConstraints().getValue(), display
						.getFerments().getValue(), display.getMicroElements()
						.getValue());
	}
}
