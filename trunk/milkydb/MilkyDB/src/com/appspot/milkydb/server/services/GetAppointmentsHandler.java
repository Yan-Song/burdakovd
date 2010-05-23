package com.appspot.milkydb.server.services;

import com.appspot.milkydb.shared.models.Appointment;

public class GetAppointmentsHandler extends
		AbstractGetEntitiesHandler<Appointment, Appointment> {

	public GetAppointmentsHandler() {
		super(Appointment.class);
	}

	@Override
	protected String getOrdering() {
		return "name";
	}

	@Override
	protected Appointment makeLightDto(final Appointment model) {
		return model;
	}
}
