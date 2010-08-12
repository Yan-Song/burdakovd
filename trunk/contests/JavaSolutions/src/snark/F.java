package snark;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Locale;
import java.util.Scanner;

public class F {

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
		final int[] x = new int[4], y = new int[4];
		Arrays.fill(x, 0);
		Arrays.fill(y, 0);

		for (int i = 0; i < 3; ++i) {
			x[i] = in.nextInt();
			y[i] = in.nextInt();
			x[3] += x[i];
			y[3] += x[i];
		}

		for (int i = 0; i < 3; ++i) {
			out.printf("%.6f, %.6f\n", 1.0 * x[3] - 2 * x[i], 1.0 * y[3] - 2
					* y[i]);
		}
	}
}
