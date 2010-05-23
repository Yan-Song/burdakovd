package com.appspot.milkydb.shared.dto;

import com.appspot.milkydb.shared.HasKey;

@SuppressWarnings("serial")
public class LightProductClass implements Dto, HasKey<Long> {

	private Long key;
	private String name;
	private Float fatness;
	private Float calorificValue;
	private TimeSpan storageLife;

	protected LightProductClass() {
	}

	public LightProductClass(final Long key, final String name,
			final Float fatness, final Float calorificValue,
			final TimeSpan storageLife) {
		this.setKey(key);
		this.setName(name);
		this.setFatness(fatness);
		this.setCalorificValue(calorificValue);
		this.setStorageLife(storageLife);
	}

	public Float getCalorificValue() {
		return calorificValue;
	}

	public Float getFatness() {
		return fatness;
	}

	@Override
	public Long getKey() {
		return key;
	}

	public String getName() {
		return name;
	}

	public TimeSpan getStorageLife() {
		return storageLife;
	}

	public void setCalorificValue(final Float calorificValue) {
		this.calorificValue = calorificValue;
	}

	public void setFatness(final Float fatness) {
		this.fatness = fatness;
	}

	@Override
	public void setKey(final Long key) {
		this.key = key;
	}

	public void setName(final String name) {
		this.name = name;
	}

	public void setStorageLife(final TimeSpan storageLife) {
		this.storageLife = storageLife;
	}
}
