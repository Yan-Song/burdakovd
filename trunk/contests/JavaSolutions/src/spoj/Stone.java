package spoj;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.io.StreamTokenizer;
import java.util.Locale;

public final class Stone {

	static {
		final Locale us = Locale.US;
		if (!Locale.getDefault().equals(us)) {
			Locale.setDefault(us);
		}
	}

	static boolean file = false;

	static StreamTokenizer in;
	static {
		try {
			// in = new Scanner(file ? new
			// FileInputStream("c:\\var\\tmp\\in.txt")
			// : System.in);
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

	/**
	 * @param args
	 * @throws IOException
	 * @throws NumberFormatException
	 */
	public static void main(final String[] args) throws NumberFormatException,
			IOException {
		try {
			final long t = nextInt();
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

	private static int nextInt() throws IOException {
		in.nextToken();
		return (int) in.nval;
	}

	static int[] X = new int[1000001];
	static int[] Y = new int[1000001];

	private static void solve(final long testId) throws IOException {
		final int n = nextInt();

		for (int i = 0; i < n; ++i) {
			X[i] = nextInt();
			Y[i] = nextInt();
		}

		X[n] = X[0];
		Y[n] = Y[0];

		long x = 0;
		long y = 0;
		long W = 0;
		for (int i = 0; i < n; ++i) {
			final long sWeight = X[i] * Y[i + 1] - X[i + 1] * Y[i];
			W += sWeight;
			x += (X[i] + X[i + 1]) * sWeight;
			y += (Y[i] + Y[i + 1]) * sWeight;
		}

		// out.println(W * 0.5);

		out.printf("%.2f %.2f\n", x / 3.0 / W, y / 3.0 / W);
	}
}
