package com.appspot.milkydb.shared.dto;

import com.appspot.milkydb.shared.HasKey;

@SuppressWarnings("serial")
public class LightProductClass implements Dto, HasKey<String> {

	public String key;
	public String name;
	public Float fatness;
	public Float calorificValue;
	public TimeSpan storageLife;

	public LightProductClass(final String key, final String name,
			final Float fatness, final Float calorificValue,
			final TimeSpan storageLife) {
		this.key = key;
		this.name = name;
		this.fatness = fatness;
		this.calorificValue = calorificValue;
		this.storageLife = storageLife;
	}

	@Override
	public String getKey() {
		return key;
	}

	@Override
	public void setKey(final String key) {
		this.key = key;
	}
}
