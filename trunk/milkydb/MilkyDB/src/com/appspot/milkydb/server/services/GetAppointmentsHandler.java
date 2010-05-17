package com.appspot.milkydb.server.services;

import java.util.ArrayList;

import javax.jdo.PersistenceManager;

import com.appspot.milkydb.server.PMF;
import com.appspot.milkydb.server.models.Appointment;
import com.appspot.milkydb.shared.dto.SerializableVoid;

public class GetAppointmentsHandler implements
		ActionHandler<SerializableVoid, ArrayList<String>> {

	@SuppressWarnings("unchecked")
	@Override
	public ArrayList<String> execute(final SerializableVoid v) {
		final PersistenceManager pm = PMF.get();

		try {
			final javax.jdo.Query query = pm.newQuery(Appointment.class);
			query.setOrdering("key asc");
			throw new NullPointerException();
			/*
			 * return new ArrayList<String>(Lists.transform( (List<Appointment>)
			 * query.execute(), new Function<Appointment, String>() {
			 * 
			 * @Override public String apply(final Appointment appointment) {
			 * return appointment.getKey().getName(); } }));
			 */
		} finally {
			pm.close();
		}
	}
}
