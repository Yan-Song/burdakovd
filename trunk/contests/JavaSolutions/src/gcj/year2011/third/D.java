package gcj.year2011.third;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;

public final class D {

	static {
		final Locale us = Locale.US;
		if (!Locale.getDefault().equals(us)) {
			Locale.setDefault(us);
		}
	}

	static boolean file = true;
	static boolean isLocal = true;

	static BufferedReader in;
	static {
		try {
			// in = new Scanner(file ? new
			// FileInputStream("c:\\var\\tmp\\in.txt")
			// : System.in);

			in = new BufferedReader(new InputStreamReader(
					file ? new FileInputStream("c:\\var\\tmp\\in.txt")
							: System.in));

			// in = new StreamTokenizer(new BufferedReader(new
			// InputStreamReader(
			// file ? new FileInputStream("c:\\var\\tmp\\in.txt")
			// : System.in)));
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
		final int t = Integer.parseInt(in.readLine());

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
		final String s = new StringBuilder(in.readLine()).reverse().toString();

		final List<Long> z = new ArrayList<Long>();
		long p = 1;
		long q = 0;
		for (int i = 0; i < s.length(); ++i) {
			if (s.charAt(i) == '?') {
				z.add(p);
			}

			if (s.charAt(i) == '1') {
				q += p;
			}

			p *= 2;
		}

		final long d = (long) 1 << z.size();

		for (long j = 0; j < d; ++j) {
			long r = q;
			for (int i = 0; i < z.size(); ++i) {
				if ((j & (long) 1 << i) != 0) {
					r += z.get(i);
				}
			}

			final long t = tryRoot(r);
			if (t > 0) {
				out.printf("Case #%d: %s\n", testId,
						new BigInteger(String.valueOf(t)).toString(2));
				return;
			}
		}

		throw new RuntimeException();
	}

	private static long tryRoot(final long r) {
		final long z = (long) Math.sqrt(r);

		for (long j = z - 100; j < z + 100; ++j) {
			if (j * j == r) {
				return j * j;
			}
		}

		return -1;
	}
}
