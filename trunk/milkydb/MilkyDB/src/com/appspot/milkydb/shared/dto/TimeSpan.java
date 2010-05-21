package com.appspot.milkydb.shared.dto;


@SuppressWarnings("serial")
public class TimeSpan implements Dto {

	private long milliseconds;

	@SuppressWarnings("unused")
	private TimeSpan() {
	}

	public TimeSpan(final long milliseconds) {
		this.milliseconds = milliseconds;
	}

	public long getMilliSeconds() {
		return milliseconds;
	}

	@Override
	public String toString() {
		return String.valueOf(milliseconds / 86400 / 1000) + " сут.";
	}
}
