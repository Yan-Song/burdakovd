package gcj.year2011.qualification;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.io.StreamTokenizer;
import java.util.Locale;

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
		final int n = nextInt();
		int t1 = 0, t2 = 0, p1 = 1, p2 = 1;

		for (int i = 0; i < n; ++i) {
			final boolean first = nextWord().equals("O");
			if (first) {
				final int dp = nextInt() - p1;
				final int dt = Math.abs(dp) + 1;
				t1 = Math.max(t1 + dt, t2 + 1);
				p1 += dp;
			} else {
				final int dp = nextInt() - p2;
				final int dt = Math.abs(dp) + 1;
				t2 = Math.max(t2 + dt, t1 + 1);
				p2 += dp;
			}
		}

		out.printf("Case #%d: %d\n", testId, Math.max(t1, t2));
	}
}
