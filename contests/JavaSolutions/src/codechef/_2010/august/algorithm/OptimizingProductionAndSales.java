package codechef._2010.august.algorithm;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Locale;

public class OptimizingProductionAndSales {

	static {
		final Locale us = Locale.US;
		if (!Locale.getDefault().equals(us)) {
			Locale.setDefault(us);
		}
	}

	static boolean file = false;

	static BufferedReader in;
	static {
		try {
			// in = new Scanner(file ? new
			// FileInputStream("c:\\var\\tmp\\in.txt")
			// : System.in);
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
			final long t = Integer.parseInt(in.readLine());
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

	private static void solve(final long testId) throws IOException {
		final String[] fs = readLine().split(" ");
		final int f = Integer.parseInt(fs[0]), s = Integer.parseInt(fs[1]);

		final double op[] = readDoubles();
		final double[][] t = new double[s][];
		for (int i = 0; i < s; ++i) {
			t[i] = readDoubles();
		}

		final int closed[] = new int[f];
		Arrays.fill(closed, 0);
		final int[] use = new int[s];

		final int[][] best = new int[100][100];
		// for(final int i = 0; i < )

		while (true) {

		}

		// printAnswer(f, s, closed, use);

	}

	private static void printAnswer(final int f, final int s,
			final int[] closed, final int[] use) {
		for (int i = 0; i < f; ++i) {
			out.printf(i == 0 ? "%s" : " %s", closed[i] == 0 ? 0 : 1);
		}
		out.println();
		for (int i = 0; i < s; ++i) {
			out.printf(i == 0 ? "%s" : " %s", use[i] + 1);
		}
		out.println();
	}

	private static String readLine() throws IOException {
		final String ans = in.readLine();
		return "".equals(ans) ? readLine() : ans;
	}

	private static double[] readDoubles() throws IOException {
		final String[] s = readLine().split(" ");
		final double[] ans = new double[s.length];
		for (int i = 0; i < s.length; ++i) {
			ans[i] = Double.parseDouble(s[i]);
		}
		return ans;
	}
}
