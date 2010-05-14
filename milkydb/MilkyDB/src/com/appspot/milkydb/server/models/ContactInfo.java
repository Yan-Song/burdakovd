package com.appspot.milkydb.server.models;

import javax.jdo.annotations.EmbeddedOnly;
import javax.jdo.annotations.PersistenceCapable;
import javax.jdo.annotations.Persistent;

import com.google.appengine.api.datastore.Text;

@PersistenceCapable
@EmbeddedOnly
public class ContactInfo {
	@Persistent
	private Text address;

	@Persistent
	private String phoneNumber;

	public Text getAddress() {
		return address;
	}

	public String getPhoneNumber() {
		return phoneNumber;
	}

	public void setAddress(final Text address) {
		this.address = address;
	}

	public void setPhoneNumber(final String phoneNumber) {
		this.phoneNumber = phoneNumber;
	}
}
