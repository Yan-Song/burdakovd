package spoj;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.io.StreamTokenizer;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Locale;
import java.util.Map;

public final class HANOICALL {

	static {
		final Locale us = Locale.US;
		if (!Locale.getDefault().equals(us)) {
			Locale.setDefault(us);
		}
	}

	static boolean file = false;

	static StreamTokenizer in;
	static {
		try {
			// in = new Scanner(file ? new
			// FileInputStream("c:\\var\\tmp\\in.txt")
			// : System.in);
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

	/**
	 * @param args
	 * @throws IOException
	 */
	public static void main(final String[] args) throws IOException {
		try {
			while (solve()) {
				;
			}
		} finally {
			out.flush();
		}
	}

	static int[][] bljad;

	private static boolean solve() throws IOException {
		final int n = nextInt();
		if (n == 0) {
			return false;
		}

		final int[] start = new int[n];
		for (int i = 0; i < n; ++i) {
			start[n - 1 - i] = nextInt();
		}

		final int[] finish = new int[n];
		for (int i = 0; i < n; ++i) {
			finish[n - 1 - i] = nextInt();
		}

		bljad = new int[3][n];
		for (int i = 0; i < bljad.length; ++i) {
			Arrays.fill(bljad[i], i + 1);
		}

		count = 0;
		out.println(solve(start, finish, 0));
		// System.err.println(count);

		return true;
	}

	private static int nextInt() throws IOException {
		in.nextToken();
		return (int) in.nval;
	}

	static final long[] pow2 = new long[33];
	static {
		pow2[0] = 1;
		for (int i = 1; i < pow2.length; ++i) {
			pow2[i] = 2 * pow2[i - 1];
		}
	}

	static final Map<Long, Long> cache = new HashMap<Long, Long>();

	static long getHash(final int[] data, final int start) {
		long ans = 137;
		final long m = 17931;
		for (int i = start; i < data.length; ++i) {
			ans = ans * m + data[i];
		}
		return ans;
	}

	static int count = 0;

	private static long solve(final int[] start, final int[] finish,
			final int first) {

		++count;
		if (start == finish) {
			return 0;
		}

		if (first == start.length) {
			return 0;
		}

		for (int i = 0; i < 3; ++i) {
			if (start == bljad[i]) {
				for (int j = 0; j < 3; ++j) {
					if (finish == bljad[j]) {
						final int n = start.length - first;
						return (1 << n) - 1;
					}
				}
			}
		}

		final long h = getHash(start, first) * 911 ^ getHash(finish, first);

		final Long cached = cache.get(h);

		if (cached == null) {

			if (start[first] == finish[first]) {
				final long ans = solve(start, finish, first + 1);
				cache.put(h, ans);
				return ans;
			} else {
				final int third = 1 + 2 + 3 - start[first] - finish[first];
				final int[] tmpFinish = bljad[third - 1];

				final long ans = solve(start, tmpFinish, first + 1) + 1
						+ solve(tmpFinish, finish, first + 1);

				cache.put(h, ans);

				return ans;
			}
		} else {
			return cached;
		}
	}
}
