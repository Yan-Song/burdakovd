package spoj;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Locale;
import java.util.Scanner;

public class MBALL {

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
			final long t = in.nextInt();
			for (long i = 0; i < t; ++i) {
				solve(i + 1);
				if (file) {
					System.out.println(i + 1 + "/" + t);
					System.out.flush();
				}
				if (!file) {
					out.flush();
				}
			}
		} finally {
			out.flush();
		}
	}

	static final int[] deltas = new int[] { 2, 3, 6, 7, 8 };
	static final int[] qdeltas = new int[] { 666, 2, 3, 6, 7, 8 };

	final static int N = 100001;
	static final long[][] dp_partial = new long[deltas.length + 1][N];

	static {
		// final long started = System.currentTimeMillis();

		// for (int tt = 0; tt < 100; ++tt)
		{

			for (int j = 0; j <= deltas.length; ++j) {
				Arrays.fill(dp_partial[j], 0);
			}

			for (int i = 0; i <= deltas.length; ++i) {
				dp_partial[i][0] = 1;
			}

			for (int _last = 0; _last < deltas.length; ++_last) {

				final int last = _last + 1;

				for (int score = 1; score < N; ++score) {

					final int scoreBefore = score - qdeltas[last];

					dp_partial[last][score] = scoreBefore >= 0 ? dp_partial[_last][score]
							+ dp_partial[last][scoreBefore]
							: dp_partial[_last][score];

				}
			}
		}

		// System.out.println("Time: " + (System.currentTimeMillis() - started)
		// + " ms.");
	}

	private static void solve(final long testId) {
		final int s = in.nextInt();

		out.println(s == 0 ? 1 : dp_partial[deltas.length][s]);
	}
}
