/**
 * 
 */
package com.appspot.milkydb.client.presenter;

import com.appspot.milkydb.client.service.ManagedAsyncService;
import com.appspot.milkydb.shared.dto.SingleKey;
import com.appspot.milkydb.shared.models.Contract;
import com.appspot.milkydb.shared.models.TimeSpan;
import com.google.gwt.event.shared.HandlerManager;
import com.google.gwt.user.client.ui.HasValue;

/**
 * @author burdakovd
 * 
 */
public abstract class AbstractEditContractPresenter<M extends Contract> extends
		AbstractEditEntityPresenter<M> {

	public interface Display extends AbstractEditEntityPresenter.Display {
		HasValue<String> getCount();

		HasValue<TimeSpan> getFrequency();

	}

	private final Display display;

	/**
	 * @param display
	 * @param service
	 * @param localEventBus
	 * @param eventBus
	 */
	public AbstractEditContractPresenter(final Display display,
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
	public AbstractEditContractPresenter(final Display display,
			final ManagedAsyncService service,
			final HandlerManager localEventBus, final HandlerManager eventBus,
			final SingleKey key) {
		super(display, service, localEventBus, eventBus, key);
		this.display = display;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * com.appspot.milkydb.client.presenter.AbstractEditEntityPresenter#displayDto
	 * (com.appspot.milkydb.shared.dto.Dto)
	 */
	@Override
	protected void displayDto(final M data) {
		display.getFrequency().setValue(data.getFrequency());
		display.getCount().setValue(String.valueOf(data.getCount()));
	}
}
