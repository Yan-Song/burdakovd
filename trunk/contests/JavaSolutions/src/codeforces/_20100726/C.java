package codeforces._20100726;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.Scanner;

public class C {

	private static final BigInteger TWO = new BigInteger("2");

	static boolean file = false;

	static Scanner in;
	static {
		try {
			in = new Scanner(file ? new FileInputStream("c:\\var\\tmp\\in.txt")
					: System.in);
			// in = new BufferedReader(new InputStreamReader(
			// file ? new FileInputStream("c:\\var\\tmp\\in.txt")
			// : System.in));
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

	private static class Matrix {
		final static Matrix ONE = new Matrix() {
			{
				for (int i = 0; i < size; ++i) {
					for (int j = 0; j < size; ++j) {
						set(i, j, i == j ? BigInteger.ONE : BigInteger.ZERO);
					}
				}
			}
		};

		final static int size = 3;

		BigInteger[][] data = new BigInteger[3][3];

		Matrix() {
		}

		BigInteger get(final int i, final int j) {
			return data[i][j];
		}

		void set(final int i, final int j, final BigInteger value) {
			data[i][j] = value;
		}

		void set(final int i, final int j, final int value) {
			data[i][j] = new BigInteger(String.valueOf(value));
		}

		public Matrix multiply(final Matrix m) {
			final Matrix ans = new Matrix();

			for (int i = 0; i < size; ++i) {
				for (int j = 0; j < size; ++j) {
					BigInteger accumulator = BigInteger.ZERO;
					for (int k = 0; k < size; ++k) {
						accumulator = accumulator.add(get(i, k).multiply(
								m.get(k, j)));
					}
					ans.set(i, j, accumulator);
				}
			}

			return ans;
		}

		public BigInteger[] multiply(final BigInteger[] v) {
			final BigInteger[] ans = new BigInteger[3];

			for (int i = 0; i < size; ++i) {
				BigInteger accumulator = BigInteger.ZERO;
				for (int j = 0; j < size; ++j) {
					accumulator = accumulator.add(get(i, j).multiply(v[j]));
				}
				ans[i] = accumulator;
			}

			return ans;
		}
	}

	private static void solve() {
		final int n = in.nextInt();
		final long N = in.nextLong();

		final BigInteger[] m0 = readPoint();

		final Matrix[] part = new Matrix[n + 1];
		part[0] = Matrix.ONE;

		for (int i = 0; i < n; ++i) {
			final BigInteger[] a = readPoint();
			final Matrix m = new Matrix();
			m.set(0, 0, -1);
			m.set(0, 1, 0);
			m.set(0, 2, a[0].multiply(TWO));
			m.set(1, 0, 0);
			m.set(1, 1, -1);
			m.set(1, 2, a[1].multiply(TWO));
			m.set(2, 0, 0);
			m.set(2, 1, 0);
			m.set(2, 2, 1);
			part[i + 1] = m.multiply(part[i]);
		}

		final Matrix mans = part[(int) (N % n)].multiply(fastPower(part[n], N
				/ n));
		final BigInteger[] ans = mans.multiply(m0);
		out.print(ans[0].toString());
		out.print(" ");
		out.println(ans[1].toString());
	}

	private static Matrix fastPower(final Matrix matrix, final long p) {
		if (p == 0) {
			return Matrix.ONE;
		}
		if ((p & 1) == 1) {
			return matrix.multiply(fastPower(matrix, p - 1));
		} else {
			final Matrix p2 = fastPower(matrix, p / 2);
			return p2.multiply(p2);
		}
	}

	private static BigInteger[] readPoint() {
		return new BigInteger[] { new BigInteger(in.next()),
				new BigInteger(in.next()), BigInteger.ONE };
	}
}
