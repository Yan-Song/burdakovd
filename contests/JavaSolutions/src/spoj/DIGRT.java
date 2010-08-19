package spoj;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Locale;
import java.util.Scanner;

public class DIGRT {

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

	static int[][] partial = new int[10][65536];

	static {
		for (int j = 0; j < 10; ++j) {
			partial[j][0] = 0;
		}

		for (int n = 1; n <= 50000; ++n) {
			final int rt = root(n);
			for (int d = 0; d < 10; ++d) {
				partial[d][n] = partial[d][n - 1];
				if (d == rt) {
					++partial[d][n];
				}
			}
		}
	}

	private static void solve(final long testId) {
		final int n = in.nextInt();

		for (int i = 1; i < 10; ++i) {
			out.print((i == 1 ? "" : " ") + partial[i][n]);
		}
		out.println();
	}

	private static int root(int n) {
		if (n < 10) {
			return n;
		}

		int sum = 0;
		while (n > 0) {
			sum += n % 10;
			n /= 10;
		}

		return root(sum);
	}
}
