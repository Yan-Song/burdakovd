package codeforces._20100726;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Locale;
import java.util.Map;
import java.util.Scanner;

public class B {

	static {
		final Locale us = Locale.US;
		if (!Locale.getDefault().equals(us)) {
			Locale.setDefault(us);
		}
	}

	static boolean file = false;

	static Scanner in;
	static {
		try {
			in = new Scanner(file ? new FileInputStream("f:\\var\\tmp\\in.txt")
					: System.in);
			// in = new BufferedReader(new InputStreamReader(
			// file ? new FileInputStream("f:\\var\\tmp\\in.txt")
			// : System.in));
		} catch (final FileNotFoundException e) {
			e.printStackTrace();
		}
	}

	static PrintWriter out;
	static {
		try {
			out = file ? new PrintWriter(
					new FileWriter("f:\\var\\tmp\\out.txt")) : new PrintWriter(
					System.out);
		} catch (final IOException e) {
			e.printStackTrace();
		}
	}

	/**
	 * @param args
	 */
	public static void main(final String[] args) {
		try {
			solve();
		} finally {
			out.flush();
		}
	}

	private static class Racer {
		String name;
		int[] score1;
		int[] score2;
		final static int[] values = new int[] { 25, 18, 15, 12, 10, 8, 6, 4, 2,
				1 };

		public Racer(final String name) {
			this.name = name;
			score1 = new int[100];
			score2 = new int[100];
			Arrays.fill(score1, 0);
			Arrays.fill(score2, 0);
		}

		public void process(final int place) {
			if (place - 1 < values.length) {
				processValue(values[place - 1]);
			}
			processPlace(place);
		}

		private void processPlace(final int place) {
			if (place == 1) {
				++score1[1];
				++score2[0];
			} else {
				++score1[place];
				++score2[place];
			}
		}

		private void processValue(final int value) {
			score1[0] += value;
			score2[1] += value;
		}

	}

	private static void solve() {
		final int t = in.nextInt();
		final Map<String, Racer> racers = new HashMap<String, B.Racer>();

		for (int ti = 0; ti < t; ++ti) {
			final int n = in.nextInt();

			for (int i = 0; i < n; ++i) {
				final String name = in.next();
				if (!racers.containsKey(name)) {
					racers.put(name, new Racer(name));
				}
				racers.get(name).process(i + 1);
			}
		}

		Racer max1 = racers.values().iterator().next();
		Racer max2 = max1;

		for (final Racer candidate : racers.values()) {
			if (gt(candidate.score1, max1.score1)) {
				max1 = candidate;
			}

			if (gt(candidate.score2, max2.score2)) {
				max2 = candidate;
			}
		}

		out.println(max1.name);
		out.println(max2.name);
	}

	private static boolean gt(final int[] x, final int[] y) {
		for (int i = 0; i < x.length; ++i) {
			if (x[i] > y[i]) {
				return true;
			} else if (x[i] < y[i]) {
				return false;
			}
		}
		return false;
	}
}
