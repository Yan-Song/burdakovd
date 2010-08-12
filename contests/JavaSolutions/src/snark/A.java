package snark;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Locale;
import java.util.Scanner;

public class A {

	private static final int _20 = 1 << 20;
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
		final int n = in.nextInt();
		final String mask = in.next();

		final boolean[] dp = new boolean[_20];
		Arrays.fill(dp, false);

		for (int i = 0; i < dp.length; ++i) {
			for (int j = 0; j < 20; ++j) {
				if ((i & 1 << j) != 0) {
					dp[i] |= !dp[i & ~(1 << j | 1 << j + 1 | 1 << j - 1)];
				}
			}
		}

		int q = 0;
		for (int i = 0; i < n; ++i) {
			if (mask.charAt(i) != 'X') {
				q |= 1 << i;
			}
		}

		out.println(dp[q] ? "Yes" : "No");
	}
}
