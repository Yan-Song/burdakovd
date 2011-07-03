package gcj.year2011.second;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Locale;

public final class B {

	static {
		final Locale us = Locale.US;
		if (!Locale.getDefault().equals(us)) {
			Locale.setDefault(us);
		}
	}

	static boolean file = true;
	static boolean isLocal = true;

	private static String nextLine() throws IOException {
		return in.readLine();
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
			final int t = Integer.parseInt(nextLine());
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
		final String[] _hline = nextLine().split(" ");
		final int r = Integer.parseInt(_hline[0]);
		final int c = Integer.parseInt(_hline[1]);

		final long d = Integer.parseInt(_hline[2]);

		final long[][] sums = new long[r + 1][c + 1];
		final long[][] xMoments = new long[r + 1][c + 1];
		final long[][] yMoments = new long[r + 1][c + 1];

		for (final long[] q : sums) {
			Arrays.fill(q, 0);
		}

		for (final long[] q : xMoments) {
			Arrays.fill(q, 0);
		}

		for (final long[] q : yMoments) {
			Arrays.fill(q, 0);
		}

		for (int i = 1; i <= r; ++i) {
			final String line = nextLine();
			for (int j = 1; j <= c; ++j) {
				final long cur = d + line.charAt(j - 1) - '0';
				sums[i][j] = sums[i - 1][j] + sums[i][j - 1]
						- sums[i - 1][j - 1] + cur;
				final long xCur = cur * j, yCur = cur * i;
				xMoments[i][j] = xMoments[i - 1][j] + xMoments[i][j - 1]
						- xMoments[i - 1][j - 1] + xCur;
				yMoments[i][j] = yMoments[i - 1][j] + yMoments[i][j - 1]
						- yMoments[i - 1][j - 1] + yCur;
			}
		}

		for (int k = Math.min(r, c); k >= 3; --k) {
			for (int xStart = 1; xStart + k - 1 <= c; ++xStart) {
				for (int yStart = 1; yStart + k - 1 <= r; ++yStart) {

					final int xFinish = xStart + k - 1;
					final int yFinish = yStart + k - 1;

					final long m = sums[yFinish - 1][xFinish]
							+ sums[yFinish][xFinish - 1]
							- sums[yFinish - 1][xFinish - 1]
							+ sums[yFinish - 1][xStart] - sums[yFinish][xStart]
							- sums[yFinish - 1][xStart - 1]
							+ sums[yStart][xFinish - 1] - sums[yStart][xFinish]
							- sums[yStart - 1][xFinish - 1]
							+ sums[yStart][xStart - 1]
							+ sums[yStart - 1][xStart] - sums[yStart][xStart];

					if ((xStart + xFinish) * m == 2 * (xMoments[yFinish - 1][xFinish]
							+ xMoments[yFinish][xFinish - 1]
							- xMoments[yFinish - 1][xFinish - 1]
							+ xMoments[yFinish - 1][xStart]
							- xMoments[yFinish][xStart]
							- xMoments[yFinish - 1][xStart - 1]
							+ xMoments[yStart][xFinish - 1]
							- xMoments[yStart][xFinish]
							- xMoments[yStart - 1][xFinish - 1]
							+ xMoments[yStart][xStart - 1]
							+ xMoments[yStart - 1][xStart] - xMoments[yStart][xStart])
							&& (yStart + yFinish) * m == 2 * (yMoments[yFinish - 1][xFinish]
									+ yMoments[yFinish][xFinish - 1]
									- yMoments[yFinish - 1][xFinish - 1]
									+ yMoments[yFinish - 1][xStart]
									- yMoments[yFinish][xStart]
									- yMoments[yFinish - 1][xStart - 1]
									+ yMoments[yStart][xFinish - 1]
									- yMoments[yStart][xFinish]
									- yMoments[yStart - 1][xFinish - 1]
									+ yMoments[yStart][xStart - 1]
									+ yMoments[yStart - 1][xStart] - yMoments[yStart][xStart])) {
						// success
						out.printf("Case #%d: %d\n", testId, k);
						return;
					}
				}
			}
		}

		out.printf("Case #%d: IMPOSSIBLE\n", testId);
	}
}
