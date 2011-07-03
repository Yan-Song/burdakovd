package codechef._2010.december.algorithm;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.util.Locale;

public final class ODDBIN {

	static {
		final Locale us = Locale.US;
		if (!Locale.getDefault().equals(us)) {
			Locale.setDefault(us);
		}
	}

	static boolean file = false;
	static boolean isLocal = true;

	private static long[] nextLongs() throws IOException {
		final String s = in.readLine().trim();
		final String[] ns = s.split(" ");
		final long[] ans = new long[ns.length];
		for (int i = 0; i < ns.length; ++i) {
			ans[i] = Long.parseLong(ns[i]);
		}
		return ans;
	}

	private static int[] nextInts() throws IOException {
		final String s = in.readLine().trim();
		final String[] ns = s.split(" ");
		final int[] ans = new int[ns.length];
		for (int i = 0; i < ns.length; ++i) {
			ans[i] = Integer.parseInt(ns[i]);
		}
		return ans;
	}

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
		try {
			final long startTime = System.nanoTime();
			final long t = nextInt();
			for (long i = 0; i < t; ++i) {
				solve(i + 1);
				if (file) {
					err.println(i + 1 + "/" + t);
				}
				if (!file) {
					out.flush();
				}
			}
			if (isLocal) {
				err.println(String.format("Completed after %d ms.",
						(System.nanoTime() - startTime) / 1000000));
			}
		} finally {
			out.flush();
		}
	}

	private static int nextInt() throws IOException {
		final int[] ans = nextInts();
		if (ans.length == 1) {
			return ans[0];
		} else {
			throw new IOException();
		}
	}

	private static void solve(final long testId) throws IOException {

		final long[] input = nextLongs();
		final int m = (int) input[0];

		for (int i = 0; i < m; ++i) {
			input[i] = input[i + 1];
		}

		long ans = 0;

		for (int owners = 1; owners < 1 << m; ++owners) {

			final long mask = commonMask(input, m, owners);
			final int commonBits = countBits(mask);
			final long commonPower = 1L << commonBits;

			final int ownersCount = countBits(owners);
			final int ownersMultiplier = (ownersCount & 1) == 0 ? -(1 << ownersCount - 1)
					: 1 << ownersCount - 1;
			final long delta = ownersMultiplier * commonPower;

			// err.println(String
			// .format("For owners=%d, commonMask=%d, commonBits = %d, commonPower = %d, ownersCount = %d, ownersMultiplier = %d, add %d to answer",
			// owners, mask, commonBits, commonPower, ownersCount,
			// ownersMultiplier, delta));

			ans += delta;
		}

		out.println(ans);
	}

	private static long commonMask(final long[] input, final int m,
			final int owners) {

		long mask = ~0L;
		for (int i = 0; i < m; ++i) {
			if ((owners & 1 << i) != 0) {
				mask &= input[i];
			}
		}
		return mask;
	}

	private static int countBits(final long mask) {
		int ans = 0;
		for (long i = mask; i != 0; i &= i - 1) {
			++ans;
		}
		return ans;
	}
}
