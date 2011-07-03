package codeforces._20100726;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Locale;
import java.util.Scanner;

public class A {

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

	private static void solve() {
		final int n = in.nextInt();
		final int[] a = new int[n];
		final int[] b = new int[n];
		final int[] c = new int[n];
		final boolean[] used = new boolean[n];

		int total = 0;
		for (int i = 0; i < n; ++i) {
			a[i] = in.nextInt() - 1;
			b[i] = in.nextInt() - 1;
			c[i] = in.nextInt();
			used[i] = false;
			total += c[i];
		}

		int current = 0;
		int first = 0;

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (!used[j]) {
					if (current == a[j]) {
						current = b[j];
						used[j] = true;
						break;
					} else if (current == b[j]) {
						first += c[j];
						current = a[j];
						used[j] = true;
						break;
					}
				}
			}
		}

		assert current == 0;
		final int second = total - first;

		out.println(Math.min(first, second));
	}
}
