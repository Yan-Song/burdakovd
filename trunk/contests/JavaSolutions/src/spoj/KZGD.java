package spoj;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;
import java.util.Scanner;

public class KZGD {

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

	static List<BigInteger> c = new ArrayList<BigInteger>();
	static {
		c.add(BigInteger.ONE);

		for (BigInteger q = BigInteger.ONE; c.size() < 510; q = q
				.add(BigInteger.ONE)) {

			final String s = q.toString(2);
			int n = 0;
			for (final char c : s.toCharArray()) {
				if (c == '1') {
					++n;
				}
			}

			if ((n & 1) == 1) {
				c.add(q);
			}
		}
	}

	private static void solve(final long testId) {
		out.println(c.get(in.nextInt()).toString());
	}
}
