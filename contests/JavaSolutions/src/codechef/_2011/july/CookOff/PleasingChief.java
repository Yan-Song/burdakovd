package codechef._2011.july.CookOff;
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

public final class PleasingChief {

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
	private static int[] prices;
	private static int[] discounts;
	static {
		err = System.err;
	}

	/**
	 * @param args
	 * @throws IOException
	 */
	public static void main(final String[] args) throws IOException {

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

		out.flush();
		if (file) {
			out.close();
		}

	}

	private static void solve(final int testId) throws IOException {
		final int n = nextInt();
		final int k = nextInt();

		prices = new int[n];
		for (int i = 0; i < n; ++i) {
			prices[i] = nextInt();
		}

		discounts = new int[k];
		for (int i = 0; i < k; ++i) {
			discounts[i] = nextInt();
		}

		Arrays.sort(prices);
		Arrays.sort(discounts);

		clearCache();
		for (int i = 1; i <= n; ++i) {
			for (int j = Math.max(1, k - (n - i)); j <= k && j <= i; ++j) {
				cache[i][j] = solve_(i, j);
			}
		}
		out.printf("%.3f\n", solve(n, k) / 100);
	}

	private static void reverse(final int[] x) {
		for (int i = 0, j = x.length - 1; i < j; ++i, --j) {
			final int t = x[i];
			x[i] = x[j];
			x[j] = t;
		}
	}

	static double[][] cache = new double[1001][1001];

	private static void clearCache() {
		for (final double[] row : cache) {
			Arrays.fill(row, 0.0);
		}
	}

	private static double solve(final int n, final int k) {
		// if (!Double.isNaN(cached)) {
		return cache[n][k];
		// }
		// final double calculated = solve_(n, k);
		// cache[n][k] = calculated;
		// return calculated;
	}

	private static double solve_(final int n, final int k) {
		if (k == 0) {
			return 0.0;
		}
		if (k > n) {
			return 0.0;
		}

		return (k * (discounts[k - 1] * prices[n - 1] + solve(n - 1, k - 1)) + (n - k)
				* solve(n - 1, k))
				/ n;
	}
}
