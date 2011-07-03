package codechef._2010.december.algorithm;

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

public final class HBEAR {

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
		if (in.ttype == StreamTokenizer.TT_NUMBER) {
			return (int) in.nval;
		} else {
			throw new IOException();
		}
	}

	private static String nextString() throws IOException {
		in.nextToken();
		if (in.ttype == StreamTokenizer.TT_WORD) {
			return in.sval;
		} else {
			throw new IOException();
		}
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
			final long t = 1;// nextInt();
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

	private static void solve(final long testId) throws IOException {
		final int n = nextInt();
		final int m = nextInt();
		final int k = nextInt();

		final boolean[][] map = readMap(n, m);

		final int[][] shiftedPartialCounts = new int[n + 1][m + 1];
		for (final int[] row : shiftedPartialCounts) {
			Arrays.fill(row, 0);
		}

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				shiftedPartialCounts[i + 1][j + 1] = shiftedPartialCounts[i][j + 1]
						+ shiftedPartialCounts[i + 1][j]
						- shiftedPartialCounts[i][j] + (map[i][j] ? 1 : 0);
			}
		}

		final int[][] deltasForHeight = new int[n + 1][m + 2];
		for (final int[] row : deltasForHeight) {
			Arrays.fill(row, 0);
		}

		for (int height = 1; height <= n; ++height) {
			for (int vOffset = 0; vOffset + height <= n; ++vOffset) {
				int rightBound = 0;
				for (int hOffset = 0; hOffset < m; ++hOffset) {
					// двигаем правую границу вправо, пока не будет нужное
					// количество
					while (rightBound < m
							&& !isEnough(shiftedPartialCounts, vOffset, height,
									hOffset, rightBound, k)) {
						++rightBound;
					}

					// теперь мы знаем минимальную ширину блока, заданной высоты
					// и в заданной позиции
					final int minWidth = rightBound - hOffset + 1;
					final int maxWidth = m - hOffset;
					++deltasForHeight[height][minWidth];
					--deltasForHeight[height][maxWidth + 1];

					if (rightBound == m) {
						break;
					}
				}
			}
		}

		// concreteAnswer[i][j] - количество прямоугольников заданного размера,
		// имеющих хотя бы k элементов с медом
		final long[][] concreteAnswer = new long[n + 1][m + 1];
		for (final long[] row : concreteAnswer) {
			Arrays.fill(row, 0);
		}

		for (int i = 1; i <= n; ++i) {
			concreteAnswer[i][0] = deltasForHeight[i][0];
			for (int j = 1; j <= m; ++j) {
				concreteAnswer[i][j] = concreteAnswer[i][j - 1]
						+ deltasForHeight[i][j];
			}
		}

		final long[][] cumulativeAnswer = new long[n + 1][m + 1];
		for (final long[] row : cumulativeAnswer) {
			Arrays.fill(row, 0);
		}

		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				cumulativeAnswer[i][j] = cumulativeAnswer[i - 1][j]
						+ cumulativeAnswer[i][j - 1]
						- cumulativeAnswer[i - 1][j - 1] + concreteAnswer[i][j];
			}
		}

		final int q = nextInt();

		for (int i = 0; i < q; ++i) {
			final int a = nextInt();
			final int b = nextInt();

			out.println(cumulativeAnswer[a][b]);
		}

	}

	private static boolean isEnough(final int[][] shiftedPartialCounts,
			final int vOffset, final int height, final int hOffset,
			final int rightBound, final int k) {

		final int actualCount = shiftedPartialCounts[vOffset + height][rightBound + 1]
				- shiftedPartialCounts[vOffset + height][hOffset]
				- shiftedPartialCounts[vOffset][rightBound + 1]
				+ shiftedPartialCounts[vOffset][hOffset];

		return actualCount >= k;

	}

	private static boolean[][] readMap(final int n, final int m)
			throws IOException {

		in.ordinaryChar('.');
		in.ordinaryChar('H');

		final boolean[][] map = new boolean[n][m];
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				in.nextToken();
				final char c = (char) in.ttype;
				if (c != 'H' && c != '.') {
					throw new IOException();
				}
				map[i][j] = c == 'H';
			}
		}

		return map;
	}
}
