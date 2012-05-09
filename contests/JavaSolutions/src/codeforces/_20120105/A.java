package codeforces._20120105;
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

public class A {

	static {
		final Locale us = Locale.US;
		if (!Locale.getDefault().equals(us)) {
			Locale.setDefault(us);
		}
	}

	static boolean file = false;
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
		final int t = 1;// nextInt();

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

	private static void Assert(final boolean x) {
		if (!x) {
			System.err.println("Assertion failed");
		}
	}

	private static void solve(final int testId) throws IOException {

		Assert(solve(4, 10, 4));
		Assert(!solve(5, 10, 4));
		Assert(solve(1, 10, 10));
		Assert(solve(1, 10, 9));
		Assert(!solve(1, 9, 10));
		Assert(!solve(6, 1, 7));
		Assert(solve(6, 7, 1));
		Assert(solve(6, 3, 1));
		Assert(!solve(85, 449, 16));

		if (true) {
			// return;
		}

		int n, R, r;
		n = nextInt();
		R = nextInt();
		r = nextInt();

		System.out.println(solve(n, R, r) ? "YES" : "NO");
	}

	private static boolean solve(final int n, final int R, final int r) {

		if (n == 1) {
			return r <= R;
		}

		if (n == 2) {
			return 2 * r <= R;
		}

		if (r >= R) {
			return false;
		}

		System.out.println(Math.sin(Math.PI / n));
		System.out.println(" >=");
		System.out.println(1.0 * r / (R - r));

		if (n == 6) {
			return R >= 3 * r;
		}

		return Math.sin(Math.PI / n) >= 1.0 * r / (R - r);
	}
}
