package com.appspot.milkydb.server.models;

import javax.jdo.annotations.IdGeneratorStrategy;
import javax.jdo.annotations.IdentityType;
import javax.jdo.annotations.Inheritance;
import javax.jdo.annotations.InheritanceStrategy;
import javax.jdo.annotations.PersistenceCapable;
import javax.jdo.annotations.Persistent;
import javax.jdo.annotations.PrimaryKey;

import com.appspot.milkydb.shared.models.TimeSpan;

@PersistenceCapable(identityType = IdentityType.APPLICATION)
@Inheritance(strategy = InheritanceStrategy.SUBCLASS_TABLE)
public class Contract {
	@PrimaryKey
	@Persistent(valueStrategy = IdGeneratorStrategy.IDENTITY)
	private Long id;

	@Persistent(serialized = "true")
	private TimeSpan frequency;

	@Persistent
	private Integer count;

	public Integer getCount() {
		return count;
	}

	public TimeSpan getFrequency() {
		return frequency;
	}

	public Long getId() {
		return id;
	}

	public void setCount(final Integer count) {
		this.count = count;
	}

	public void setFrequency(final TimeSpan frequency) {
		this.frequency = frequency;
	}

}
