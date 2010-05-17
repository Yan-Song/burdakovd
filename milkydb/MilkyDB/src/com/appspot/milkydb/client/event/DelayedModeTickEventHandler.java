package com.appspot.milkydb.client.event;

import com.google.gwt.event.shared.EventHandler;

public interface DelayedModeTickEventHandler extends EventHandler {

	void onDelayedModeTick(DelayedModeTickEvent delayedModeTickEvent);

}
