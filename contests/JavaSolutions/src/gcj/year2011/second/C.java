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
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Locale;

public final class C {

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

	private static long nextLong() throws IOException {
		in.nextToken();
		return (long) in.nval;
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
	private static List<Long> PRIMES;
	static {
		err = System.err;
	}

	/**
	 * @param args
	 * @throws IOException
	 */
	public static void main(final String[] args) throws IOException {
		PRIMES = makePrimes(1000000);
		try {
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
		} finally {
			out.flush();
			if (file) {
				out.close();
			}
		}
	}

	private static void solve(final int testId) throws IOException {
		final long n = nextLong();

		final int delta = calculate(n);
		out.printf("Case #%d: %d\n", testId, delta);
	}

	private static int calculate(final long n) {

		if (n == 1) {
			return 0;
		}

		int delta = 1;

		for (final long q : PRIMES) {
			long z = q * q;
			if (z > n) {
				break;
			}
			while (z <= n) {
				++delta;
				z *= q;
			}
		}

		return delta;
	}

	private static List<Long> makePrimes(final int n) {

		final boolean[] sieve = new boolean[n + 1];
		Arrays.fill(sieve, true);
		int p = 2;

		final List<Long> primes = new ArrayList<Long>();

		while (true) {
			// err.printf("Adding %d\n", p);
			primes.add((long) p);

			for (int i = p; i <= n; i += p) {
				sieve[i] = false;
			}

			while (p <= n && !sieve[p]) {
				++p;
			}
			if (p > n) {
				return primes;
			}
		}

	}
}
