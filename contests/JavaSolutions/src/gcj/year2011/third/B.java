package gcj.year2011.third;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.io.StreamTokenizer;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Locale;

public final class B {

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
		out.printf("Case #%d: %d\n", testId, solve());
	}

	private static int solve() throws IOException {
		final int n = nextInt();

		if (n == 0) {
			return 0;
		}

		final int[] counts = new int[11000];
		Arrays.fill(counts, 0);

		for (int i = 0; i < n; ++i) {
			final int x = nextInt();
			++counts[x];
		}

		final List<Integer> starts = new ArrayList<Integer>();
		final List<Integer> ends = new ArrayList<Integer>();

		for (int i = 1; i < counts.length; ++i) {
			final int sc = counts[i] - counts[i - 1];
			for (int j = 0; j < sc; ++j) {
				starts.add(i);
			}
			final int ec = -sc;
			for (int j = 0; j < ec; ++j) {
				ends.add(i);
			}
		}

		int ans = Integer.MAX_VALUE;

		for (int i = 0; i < starts.size(); ++i) {
			ans = Math.min(ans, ends.get(i) - starts.get(i));
		}

		return ans;
	}
}
