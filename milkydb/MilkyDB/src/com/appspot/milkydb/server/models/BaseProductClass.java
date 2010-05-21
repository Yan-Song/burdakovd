package com.appspot.milkydb.server.models;

import java.util.List;

import javax.jdo.annotations.IdGeneratorStrategy;
import javax.jdo.annotations.IdentityType;
import javax.jdo.annotations.Inheritance;
import javax.jdo.annotations.InheritanceStrategy;
import javax.jdo.annotations.PersistenceCapable;
import javax.jdo.annotations.Persistent;
import javax.jdo.annotations.PrimaryKey;

import com.appspot.milkydb.shared.HasKey;
import com.appspot.milkydb.shared.dto.TimeSpan;
import com.google.appengine.api.datastore.Key;
import com.google.appengine.api.datastore.Text;

@PersistenceCapable(identityType = IdentityType.APPLICATION)
@Inheritance(strategy = InheritanceStrategy.SUBCLASS_TABLE)
public class BaseProductClass implements HasKey<Key> {
	@PrimaryKey
	@Persistent(valueStrategy = IdGeneratorStrategy.IDENTITY)
	private Key key;

	@Persistent
	private String name;

	@Persistent
	private Float fatness;

	@Persistent
	private Float calorificValue;

	@Persistent(serialized = "true")
	private TimeSpan storageLife;

	@Persistent
	private String packing;

	@Persistent
	private Text storageConstraints;

	@Persistent
	private Text transportationConstraints;

	@Persistent
	private List<String> ferments;

	@Persistent
	private List<String> microElements;

	public Float getCalorificValue() {
		return calorificValue;
	}

	public Float getFatness() {
		return fatness;
	}

	public List<String> getFerments() {
		return ferments;
	}

	public Key getKey() {
		return key;
	}

	public List<String> getMicroElements() {
		return microElements;
	}

	public String getName() {
		return name;
	}

	public String getPacking() {
		return packing;
	}

	public Text getStorageConstraints() {
		return storageConstraints;
	}

	public TimeSpan getStorageLife() {
		return storageLife;
	}

	public Text getTransportationConstraints() {
		return transportationConstraints;
	}

	public void setCalorificValue(final Float calorificValue) {
		this.calorificValue = calorificValue;
	}

	public void setFatness(final Float fatness) {
		this.fatness = fatness;
	}

	public void setFerments(final List<String> ferments) {
		this.ferments = ferments;
	}

	public void setKey(final Key key) {
		this.key = key;
	}

	public void setMicroElements(final List<String> microElements) {
		this.microElements = microElements;
	}

	public void setName(final String name) {
		this.name = name;
	}

	public void setPacking(final String packing) {
		this.packing = packing;
	}

	public void setStorageConstraints(final Text storageConstraints) {
		this.storageConstraints = storageConstraints;
	}

	public void setStorageLife(final TimeSpan storageLife) {
		this.storageLife = storageLife;
	}

	public void setTransportationConstraints(
			final Text transportationConstraints) {
		this.transportationConstraints = transportationConstraints;
	}
}
