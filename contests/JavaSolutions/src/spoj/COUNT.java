package spoj;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class COUNT {

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
			while (solve()) {
				;
			}
		} finally {
			out.flush();
		}
	}

	static int[][] dp = new int[5001][5001];

	static int get(final int n, final int k) {
		if (n < 0 || k < 0) {
			return 0;
		} else if (n == 0 && k == 0) {
			return 1;
		} else {
			return dp[n][k] % 1988;
		}
	}

	static {
		for (int n = 0; n <= 5000; ++n) {
			for (int k = 0; k <= 5000; ++k) {
				if (n > 0 || k > 0) {
					dp[n][k] = get(n, k - 1) + get(n - k, k) % 1988;
				}
			}
		}
	}

	private static boolean solve() {
		final int n = in.nextInt(), k = in.nextInt();

		if (n == 0) {
			return false;
		} else {
			out.println(get(n - k, k) % 1988);
			return true;
		}
	}
}
