package codechef._2010.July.CookOff;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;

public class Ripple_Carry_Adder {

	static boolean file = false;

	static BufferedReader in;
	static {
		try {
			in = new BufferedReader(new InputStreamReader(
					file ? new FileInputStream("c:\\var\\tmp\\in.txt")
							: System.in));
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
			final long t = Long.valueOf(in.readLine());
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

	private static void solve(final long testId) throws NumberFormatException,
			IOException {

		in.readLine(); // n

		final String a = in.readLine(), b = in.readLine();

		final String f_b = f(b);
		final String f_a = f(a);
		// out.println("f(" + b + ") = " + f_b);
		// out.println("f(" + a + ") = " + f_a);
		out.println(substract(f_b, f_a));
	}

	public static void reverse(final char[] b) {
		int left = 0; // index of leftmost element
		int right = b.length - 1; // index of rightmost element

		while (left < right) {
			// exchange the left and right elements
			final char temp = b[left];
			b[left] = b[right];
			b[right] = temp;

			// move the bounds toward the center
			left++;
			right--;
		}
	}// endmethod reverse

	/**
	 * 
	 * @param x
	 * @param y
	 * @return x - y
	 */
	private static String substract(final String x, final String y) {

		final char[] xx = x.toCharArray(), yy = y.toCharArray();
		reverse(xx);
		reverse(yy);

		int mem = 0;

		for (int i = 0; i < y.length(); ++i) {
			if (yy[i] == '1') {
				--mem;
			}
			if (mem < 0) {
				if (xx[i] == '1') {
					++mem;
				}
				xx[i] = (mem & 1) == 0 ? '0' : '1';

				if (mem < 0) {
					mem = -1;
				}
			}
		}

		if (mem < 0) {
			int j = y.length();
			while (xx[j] == '0') {
				xx[j] = '1';
				++j;
			}
			xx[j] = '0';
		}

		reverse(xx);

		int k = 0;
		while (k < xx.length && xx[k] == '0') {
			++k;
		}
		return new String(xx, k, xx.length - k);
	}

	private static String f(final String b) {
		return substract(b + "0", ones(b));
	}

	private static String ones(final String b) {

		int ans = 0;
		for (final char c : b.toCharArray()) {
			if (c == '1') {
				++ans;
			}
		}

		final StringBuilder bans = new StringBuilder();
		while (ans > 0) {
			bans.append((ans & 1) == 0 ? '0' : '1');
			ans >>= 1;
		}

		return bans.reverse().toString();
	}
}
