package com.appspot.milkydb.server.services;

import javax.jdo.Query;

import com.appspot.milkydb.server.models.Appointment;
import com.appspot.milkydb.shared.dto.LightAppointment;

public class GetAppointmentsHandler extends
		AbstractGetEntitiesHandler<Appointment, LightAppointment> {

	public GetAppointmentsHandler() {
		super(Appointment.class);
	}

	@Override
	protected LightAppointment makeLightDto(final Appointment model) {
		return new LightAppointment(model.getKey().getName());
	}

	@Override
	protected void setOrdering(final Query query) {
		query.setOrdering("key asc");
	}
}
