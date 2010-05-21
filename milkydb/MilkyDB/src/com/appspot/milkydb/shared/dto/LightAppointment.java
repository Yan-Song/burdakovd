package com.appspot.milkydb.shared.dto;

@SuppressWarnings("serial")
public class LightAppointment implements Dto {
	private String appointment;

	@SuppressWarnings("unused")
	private LightAppointment() {
	}

	public LightAppointment(final String value) {
		appointment = value;
	}

	public String getAppointment() {
		return appointment;
	}

	public void setAppointment(final String appointment) {
		this.appointment = appointment;
	}
}
