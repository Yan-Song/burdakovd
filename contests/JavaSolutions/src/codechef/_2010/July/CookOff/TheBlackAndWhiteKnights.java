package codechef._2010.July.CookOff;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.Scanner;

public class TheBlackAndWhiteKnights {

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
			out.flush();
		}
	}

	private static void solve(final long testId) {
		final long n = in.nextInt(), m = in.nextInt();

		final BigInteger bn = new BigInteger(String.valueOf(n));
		final BigInteger bm = new BigInteger(String.valueOf(m));
		final BigInteger N = bn.multiply(bm);
		final BigInteger K = N.multiply(N.subtract(BigInteger.ONE));

		out.println(K.subtract(new BigInteger("4")
				.multiply(square(m - 2, n - 1).add(square(m - 1, n - 2)))));
	}

	private static BigInteger square(final long l, final long m) {
		if (l < 0 || m <= 0) {
			return BigInteger.ZERO;
		} else {
			return new BigInteger(String.valueOf(l * m));
		}
	}
}
