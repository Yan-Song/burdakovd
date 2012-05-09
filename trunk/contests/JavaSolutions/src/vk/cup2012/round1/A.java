package vk.cup2012.round1;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.io.StreamTokenizer;
import java.util.Arrays;
import java.util.Locale;

public class A {

	static {
		final Locale us = Locale.US;
		if (!Locale.getDefault().equals(us)) {
			Locale.setDefault(us);
		}
	}

	static boolean file = false;
	static boolean isLocal = false;

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
		final int n = nextInt();
		final int m = nextInt();
		final int x = nextInt();
		final int y = nextInt();

		final int[] a = new int[n];
		final int[] b = new int[m];

		for (int i = 0; i < n; ++i) {
			a[i] = nextInt();
		}

		for (int i = 0; i < m; ++i) {
			b[i] = nextInt();
		}

		// dp[i] сколько бронежилетов можно надеть на первых k бойцов
		final int[] ans = new int[n];
		Arrays.fill(ans, -1);
		int k = 0;

		int nextB = 0;
		for (int i = 1; i <= n; ++i) {

			while (nextB < m && a[i - 1] - x > b[nextB]) {
				++nextB;
			}

			if (nextB < m) {
				if (a[i - 1] - x <= b[nextB] && b[nextB] <= a[i - 1] + y) {
					ans[i - 1] = nextB;
					++nextB;
					++k;
				}
			}
		}

		out.println(k);
		for (int i = 0; i < n; ++i) {
			if (ans[i] != -1) {
				out.printf("%d %d\n", i + 1, ans[i] + 1);
			}
		}
		out.flush();
	}
}
