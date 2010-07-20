package gcj.year2010.third;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Locale;
import java.util.Scanner;

public class B {

	static {
		Locale.setDefault(Locale.US);
	}

	static boolean file = true;

	static Scanner in;
	static {
		try {
			in = new Scanner(file ? new FileInputStream("f:\\var\\tmp\\in.txt")
					: System.in);
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
			in.close();
			out.close();
		}
	}

	private static void solve(final long testId) {
		final Long ans = doSolve();

		out.println("Case #" + testId + ": "
				+ (ans == null ? "IMPOSSIBLE" : ans.toString()));
	}

	private static Long doSolve() {
		final int mx = 1000000;
		final long l = in.nextLong();
		final int n = in.nextInt();
		final int[] b = new int[n];
		for (int i = 0; i < n; ++i) {
			b[i] = in.nextInt();
		}

		Arrays.sort(b);
		final int best = b[b.length - 1];
		final int[] possible = new int[mx + 1];
		Arrays.fill(possible, Integer.MAX_VALUE);

		possible[0] = 0;

		for (int i = 0; i <= mx; ++i) {
			if (possible[i] != Integer.MAX_VALUE) {
				for (int j = 0; j < b.length; ++j) {
					final int m = i + b[j];
					if (m <= mx && possible[m] > possible[i] + 1) {
						possible[m] = possible[i] + 1;
					}
				}
			}
		}

		for (int i = 0; i <= mx; ++i) {
			if (possible[i] != Integer.MAX_VALUE) {
				if (i <= l && (l - i) % best == 0) {
					return Long.valueOf(possible[i] + (l - i) / best);
				}
			}
		}

		return null;
	}
}
