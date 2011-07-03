package ipsc;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Locale;
import java.util.Scanner;

public class B {

	static {
		Locale.setDefault(Locale.US);
	}

	static boolean file = true;

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
			final int t = in.nextInt();
			for (int i = 0; i < t; ++i) {
				solve(i + 1);
			}
		} finally {
			in.close();
			out.close();
		}
	}

	private static void solve(final int testId) {
		final double ax = in.nextDouble(), ay = in.nextDouble(), bx = in
				.nextDouble(), by = in.nextDouble();
		final double p = in.nextDouble(), q = in.nextDouble(), r = in
				.nextDouble();

		double ans = Math.abs(ax - bx) + Math.abs(ay - by);

		final double p1x = ax, p1y = (r - p * ax) / q;
		final double p2x = (r - q * ay) / p, p2y = ay;
		final double p3x = bx, p3y = (r - p * bx) / q;
		final double p4x = (r - q * by) / p, p4y = by;

		ans = Math.min(ans, distance(ax, ay, p1x, p1y, p3x, p3y, bx, by));
		ans = Math.min(ans, distance(ax, ay, p1x, p1y, p4x, p4y, bx, by));
		ans = Math.min(ans, distance(ax, ay, p2x, p2y, p3x, p3y, bx, by));
		ans = Math.min(ans, distance(ax, ay, p2x, p2y, p4x, p4y, bx, by));

		out.printf("%.12f\n", ans);

		if (!file) {
			out.flush();
		}
	}

	private static double distance(final double ax, final double ay,
			final double p1x, final double p1y, final double p2x,
			final double p2y, final double bx, final double by) {
		return distance(ax, ay, p1x, p1y) + distance(p1x, p1y, p2x, p2y)
				+ distance(p2x, p2y, bx, by);
	}

	private static double distance(final double ax, final double ay,
			final double p1x, final double p1y) {
		final double dx = ax - p1x, dy = ay - p1y;
		return Math.sqrt(dx * dx + dy * dy);
	}

}
