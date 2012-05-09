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

public final class Main {

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

		final int[] numbers = new int[n];
		for (int i = 0; i < n; ++i) {
			numbers[i] = nextInt();
		}
		Arrays.sort(numbers);

		final boolean[][][] prefixSums = calculatePrefixSums(n, numbers,
				(k - 1) / 2);
		final boolean[][][] suffixSums = calculateSuffixSums(n, numbers, k / 2);

		double best = Double.MAX_VALUE;

		for (int m = 0; m < n; ++m) {
			final int med = numbers[m];

			final int wanted = med * (k - 1);

			final boolean[] prefix = prefixSums[m][(k - 1) / 2];
			final boolean[] suffix = suffixSums[n - m - 1][k / 2];

			final int[] sumsLeft = new int[prefix.length];
			final int[] sumsRight = new int[suffix.length];
			int leftc = 0;
			int rightc = 0;

			for (int i = 0; i < prefix.length; ++i) {
				if (prefix[i]) {
					sumsLeft[leftc++] = i;
				}
			}

			for (int i = 0; i < suffix.length; ++i) {
				if (suffix[i]) {
					sumsRight[rightc++] = i;
				}
			}

			int i2 = rightc - 1;

			if (i2 >= 0) {
				for (int i1 = 0; i1 < leftc; ++i1) {
					while (i2 > 0
							&& Math.abs(wanted
									- (sumsLeft[i1] + sumsRight[i2 - 1])) <= Math
									.abs(wanted
											- (sumsLeft[i1] + sumsRight[i2]))) {
						--i2;
					}

					best = Math.min(best,
							Math.abs(wanted - (sumsLeft[i1] + sumsRight[i2])));
				}
			}
		}

		out.printf("%.3f\n", best / k);
	}

	private static void reverse(final int[] x) {
		for (int i = 0, j = x.length - 1; i < j; ++i, --j) {
			final int t = x[i];
			x[i] = x[j];
			x[j] = t;
		}
	}

	private static boolean[][][] calculateSuffixSums(final int n,
			final int[] numbers, final int K) {

		final int[] r_numbers = new int[numbers.length];
		System.arraycopy(numbers, 0, r_numbers, 0, numbers.length);
		reverse(r_numbers);

		return calculatePrefixSums(n, r_numbers, K);
	}

	private static boolean[][][] calculatePrefixSums(final int n,
			final int[] numbers, final int K) {

		// final boolean[] tmp = new boolean[120000];
		final boolean[][][] ans = new boolean[n + 1][K + 1][];

		ans[0][0] = new boolean[] { true }; // 0
		for (int i = 1; i <= K; ++i) {
			ans[0][i] = new boolean[0];
		}

		for (int prefixLength = 1; prefixLength <= n; ++prefixLength) {
			ans[prefixLength][0] = new boolean[] { true };

			for (int numbersUsed = 1; numbersUsed <= K; ++numbersUsed) {
				final boolean[] smaller = ans[prefixLength - 1][numbersUsed - 1];
				final int KK = smaller.length;
				final boolean[] current = new boolean[Math.max(KK == 0 ? 0 : KK
						+ numbers[prefixLength - 1],
						ans[prefixLength - 1][numbersUsed].length)];
				Arrays.fill(current, false);
				ans[prefixLength][numbersUsed] = current;

				System.arraycopy(ans[prefixLength - 1][numbersUsed], 0,
						current, 0, ans[prefixLength - 1][numbersUsed].length);

				// if (KK > 0) {

				// /System.arraycopy(current, numbers[prefixLength - 1],
				// tmp,
				// 0, KK);
				for (int i = 0, j = numbers[prefixLength - 1]; i < KK; ++i, ++j) {
					current[j] |= smaller[i];
				}

				// System.arraycopy(tmp, 0, current,
				// numbers[prefixLength - 1], KK);
				// }
			}
		}

		return ans;
	}
}
