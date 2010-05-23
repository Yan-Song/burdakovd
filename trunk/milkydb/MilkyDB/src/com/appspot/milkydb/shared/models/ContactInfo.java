package com.appspot.milkydb.shared.models;

import com.appspot.milkydb.shared.dto.Dto;
import com.google.appengine.api.datastore.Text;

@SuppressWarnings("serial")
public class ContactInfo implements Dto {
	private Text address;

	private String phoneNumber;

	@SuppressWarnings("unused")
	private ContactInfo() {
	}

	public ContactInfo(final String address, final String phone) {
		this.address = new Text(address);
		this.phoneNumber = phone;
	}

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
