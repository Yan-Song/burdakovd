package com.appspot.milkydb.server.services;

import javax.jdo.Query;

import com.appspot.milkydb.server.models.Appointment;

public class GetAppointmentsHandler extends
		AbstractGetEntitiesHandler<Appointment, String> {

	public GetAppointmentsHandler() {
		super(Appointment.class);
	}

	@Override
	protected String makeLightDto(final Appointment model) {
		return model.getKey().getName();
	}

	@Override
	protected void setOrdering(final Query query) {
		query.setOrdering("key asc");
	}
}
