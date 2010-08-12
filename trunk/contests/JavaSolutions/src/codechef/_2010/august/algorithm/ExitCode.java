package codechef._2010.august.algorithm;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Locale;
import java.util.Scanner;

public class ExitCode {

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

	public static long[] _10 = new long[15];
	static {
		_10[0] = 1;
		for (int i = 1; i < _10.length; ++i) {
			_10[i] = 10 * _10[i - 1];
		}
	}

	private static final long multiply(final long a, final long b, final long m) {
		return Long.valueOf(new BigInteger(String.valueOf(a))
				.multiply(new BigInteger(String.valueOf(b)))
				.mod(new BigInteger(String.valueOf(m))).toString());
	}

	private static final long _32 = 0x100000000L;

	private static void solve() {
		final int n = in.nextInt();
		final long a = in.nextLong(), b = in.nextLong(), g = in.nextLong();
		final int first = n / 2, second = n - first;

		final HashMap<Long, Integer> lowResults = new HashMap<Long, Integer>();

		final long[] _a = new long[20];
		_a[0] = 1;
		for (int i = 1; i < _a.length; ++i) {
			_a[i] = multiply(_a[i - 1], a, b);
		}

		final long[] alow = new long[first];
		Arrays.fill(alow, 0);
		for (int low = 0; low < _10[first]; ++low, increase(alow)) {
			long sum = 0;
			for (int i = 0; i < first; ++i) {
				sum += _a[i] * alow[i] % b;
				sum %= b;
			}
			if (!lowResults.containsKey(sum)) {
				lowResults.put(sum, low);
			}
		}

		final long[] ahigh = new long[second];
		Arrays.fill(ahigh, 0);
		for (int high = 0; high < _10[second]; ++high, increase(ahigh)) {
			long sum = 0;
			for (int i = 0; i < second; ++i) {
				sum += _a[first + i] * ahigh[i] % b;
				sum %= b;
			}
			final long complement = (g + b - sum) % b;
			if (lowResults.containsKey(complement)) {
				final long ans = high * _10[first] + lowResults.get(complement);
				String sans = String.valueOf(ans);
				while (sans.length() < n) {
					sans = "0" + sans;
				}
				out.println(sans);
				return;
			}
		}

		throw new RuntimeException("o_O");
	}

	private static void increase(final long[] alow) {
		int q = 0;
		while (q < alow.length && alow[q] == 9) {
			alow[q] = 0;
			++q;
		}

		if (q < alow.length) {
			++alow[q];
		}
	}
}
