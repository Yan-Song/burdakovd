package gcj.year2011.second;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.io.StreamTokenizer;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.Locale;
import java.util.PriorityQueue;

public final class A {

	static {
		final Locale us = Locale.US;
		if (!Locale.getDefault().equals(us)) {
			Locale.setDefault(us);
		}
	}

	static boolean file = true;
	static boolean isLocal = true;

	private static int nextInt() throws IOException {
		in.nextToken();
		return (int) in.nval;
	}

	private static String nextWord() throws IOException {
		in.nextToken();
		return in.sval;
	}

	static StreamTokenizer in;
	static {
		try {
			// in = new Scanner(file ? new
			// FileInputStream("c:\\var\\tmp\\in.txt")
			// : System.in);

			// in = new BufferedReader(new InputStreamReader(
			// file ? new FileInputStream("c:\\var\\tmp\\in.txt")
			// : System.in));

			in = new StreamTokenizer(new BufferedReader(new InputStreamReader(
					file ? new FileInputStream("c:\\var\\tmp\\in.txt")
							: System.in)));
		} catch (final FileNotFoundException e) {
			e.printStackTrace();
		}
	}

	static PrintWriter out;
	static {
		try {
			out = file ? new PrintWriter(
					new FileWriter("c:\\var\\tmp\\out.txt")) : new PrintWriter(
					System.out);
		} catch (final IOException e) {
			e.printStackTrace();
		}
	}

	static PrintStream err;
	static {
		err = System.err;
	}

	/**
	 * @param args
	 * @throws IOException
	 */
	public static void main(final String[] args) throws IOException {

		final long startTime = System.nanoTime();
		final int t = nextInt();
		for (int i = 0; i < t; ++i) {
			solve(i + 1);
			if (isLocal && file) {
				err.println(i + 1 + "/" + t);
			}
			if (isLocal && !file) {
				out.flush();
			}
		}
		if (isLocal) {
			err.println(String.format("Completed after %d ms.",
					(System.nanoTime() - startTime) / 1000000));
		}

		out.flush();
		if (file) {
			out.close();
		}

	}

	private static void solve(final int testId) throws IOException {
		final double x = nextInt();
		final double s = nextInt();
		final double r = nextInt();
		double t = nextInt();
		final int n = nextInt() + 1;

		final PriorityQueue<List<Double>> q = new PriorityQueue<List<Double>>(
				n, new Comparator<List<Double>>() {

					@Override
					public int compare(final List<Double> o1,
							final List<Double> o2) {
						return o1.get(0).compareTo(o2.get(0));
					}
				});

		{
			double l = x;

			for (int i = 1; i < n; ++i) {
				final double b = nextInt();
				final double e = nextInt();
				final double w = nextInt();
				q.add(Arrays.asList(new Double[] { w, e - b }));
				l -= e - b;
			}

			q.add(Arrays.asList(new Double[] { 0.0, l }));

		}
		double ans = 0;
		while (!q.isEmpty()) {
			// err.printf("Processing %s\n",
			// Arrays.toString(q.peek().toArray()));
			final double w = q.peek().get(0), l = q.peek().get(1);
			q.poll();

			final double tNeeded = l / (w + r);
			if (tNeeded <= t) {
				t -= tNeeded;
				ans += tNeeded;
			} else {
				ans += t + (l - (w + r) * t) / (w + s);
				t = 0;
			}
		}

		out.printf("Case #%d: %.9f\n", testId, ans);
	}
}
