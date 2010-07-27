package codeforces._20100726;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Locale;
import java.util.Scanner;

public class D {

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

	private static void solve() {
		final int n = in.nextInt(), m = in.nextInt();
		final int si = in.nextInt() - 1, sj = in.nextInt() - 1;

		if (m == 1) {
			out.println((n - 1 - si) * 2);
		} else {

			final double dp[][] = new double[n][m];

			for (int i = n - 1; i >= 0; --i) {

				if (i == n - 1) {
					for (int j = 0; j < m; ++j) {
						dp[i][j] = 0.0;
					}
				} else {
					final double[] c = new double[m], x = new double[m];

					{
						final double sumc = dp[i + 1][0];
						double sumx = 0.0;
						int count = 2;
						final double k = 1.0;

						sumx += 1;
						++count;

						c[0] = (count + sumc) / (count - k);
						x[0] = sumx / (count - k);
					}

					for (int j = 1; j < m - 1; ++j) {
						double sumc = dp[i + 1][j];
						double sumx = 0;
						double k = 1.0;
						int count = 2;

						// left
						sumc += c[j - 1];
						k += x[j - 1];
						++count;

						// right
						sumx += 1;
						++count;

						c[j] = (count + sumc) / (count - k);
						x[j] = sumx / (count - k);
					}

					{
						final int j = m - 1;
						double sumc = dp[i + 1][j];
						double count = 2;
						double k = 1.0;

						// left
						sumc += c[j - 1];
						k += x[j - 1];
						++count;

						c[j] = (count + sumc) / (count - k);
						dp[i][j] = c[j];
					}

					for (int j = m - 2; j >= 0; --j) {
						dp[i][j] = c[j] + x[j] * dp[i][j + 1];
					}
				}

			}

			out.println(dp[si][sj]);
		}
	}
}