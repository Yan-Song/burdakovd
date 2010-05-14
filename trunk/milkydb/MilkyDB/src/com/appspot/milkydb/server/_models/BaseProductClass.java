package com.appspot.milkydb.server._models;

import java.util.List;

import javax.jdo.annotations.IdGeneratorStrategy;
import javax.jdo.annotations.IdentityType;
import javax.jdo.annotations.Inheritance;
import javax.jdo.annotations.InheritanceStrategy;
import javax.jdo.annotations.PersistenceCapable;
import javax.jdo.annotations.Persistent;
import javax.jdo.annotations.PrimaryKey;

import org.joda.time.Period;

import com.google.appengine.api.datastore.Text;

@PersistenceCapable(identityType = IdentityType.APPLICATION)
@Inheritance(strategy = InheritanceStrategy.SUBCLASS_TABLE)
public class BaseProductClass {
	@PrimaryKey
	@Persistent(valueStrategy = IdGeneratorStrategy.IDENTITY)
	private Long id;

	@Persistent
	private String name;

	@Persistent
	private Float fatness;

	@Persistent
	private Float calorificValue;

	@Persistent
	// (serialized = "true")
	private Period storageLife;

	@Persistent
	private String packing;

	@Persistent
	private Text storageConstraints;

	@Persistent
	private Text transportationConstraints;

	@Persistent
	private List<Ferment> ferments;

	@Persistent
	private List<MicroElement> microElements;

	public Float getCalorificValue() {
		return calorificValue;
	}

	public Float getFatness() {
		return fatness;
	}

	public List<Ferment> getFerments() {
		return ferments;
	}

	public Long getId() {
		return id;
	}

	public List<MicroElement> getMicroElements() {
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

	public Period getStorageLife() {
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

	public void setFerments(final List<Ferment> ferments) {
		this.ferments = ferments;
	}

	public void setMicroElements(final List<MicroElement> microElements) {
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

	public void setStorageLife(final Period storageLife) {
		this.storageLife = storageLife;
	}

	public void setTransportationConstraints(
			final Text transportationConstraints) {
		this.transportationConstraints = transportationConstraints;
	}
}
