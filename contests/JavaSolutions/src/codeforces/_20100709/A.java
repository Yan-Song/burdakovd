package codeforces._20100709;

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
			if (file) {
				System.out.flush();
			}
			if (!file) {
				out.flush();
			}

		} finally {
			in.close();
			out.close();
		}
	}

	private static void solve() {
		final String s = in.next();

		int ans = 0;
		for (int l = 0; l < s.length(); ++l) {
			for (int r = l; r < s.length(); ++r) {
				for (int p = l + 1; p - l + r < s.length(); ++p) {
					boolean ok = true;

					for (int q = l, qq = p; q <= r; ++q, ++qq) {
						if (s.charAt(q) != s.charAt(qq)) {
							ok = false;
						}
					}

					if (ok) {
						ans = Math.max(ans, r - l + 1);
					}
				}
			}
		}

		out.println(ans);
	}
}
