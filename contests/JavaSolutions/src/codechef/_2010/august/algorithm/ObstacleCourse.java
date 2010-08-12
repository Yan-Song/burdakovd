package codechef._2010.august.algorithm;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Locale;
import java.util.Scanner;

public class ObstacleCourse {

	private static final double EPS = 0.0001;
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

	private static void solve(final long testId) {
		final double r = in.nextDouble(), R = in.nextDouble();
		final int n = in.nextInt();
		final int[] x = new int[n], y = new int[n];
		for (int i = 0; i < n; ++i) {
			x[i] = in.nextInt();
			y[i] = in.nextInt();
		}

		final int from = n, to = n + 1;
		final double[][] dist = new double[n + 2][n + 2];

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				dist[i][j] = Math.sqrt(sqr(x[i] - x[j]) + sqr(y[i] - y[j]));
			}
		}

		for (int i = from; i <= to; ++i) {
			for (int j = 0; j < n; ++j) {
				final double rr = i == from ? r : R;
				dist[i][j] = Math.abs(Math.sqrt(sqr(x[j]) + sqr(y[j])) - rr);
				dist[j][i] = dist[i][j];
			}
		}

		dist[from][to] = Double.MAX_VALUE;
		dist[to][from] = Double.MAX_VALUE;

		double left = 0;
		double right = Math.abs(R - r);

		while (Math.abs(left - right) > EPS) {
			final double middle = (left + right) / 2;
			if (reachable(from, to, dist, middle)) {
				right = middle;
			} else {
				left = middle;
			}
		}

		System.out.printf("%.3f\n", left);
	}

	private static boolean[] visited;

	private static boolean reachable(final int from, final int to,
			final double[][] dist, final double middle) {
		visited = new boolean[dist.length];
		Arrays.fill(visited, false);

		return dfs(from, to, dist, middle);
	}

	private static boolean dfs(final int from, final int to,
			final double[][] dist, final double middle) {

		if (visited[from]) {
			return false;
		} else {
			visited[from] = true;

			if (from == to) {
				return true;
			}

			for (int i = 0; i < dist.length; ++i) {
				if (dist[from][i] < middle && dfs(i, to, dist, middle)) {
					return true;
				}
			}
			return false;
		}
	}

	private static int sqr(final int i) {
		return i * i;
	}
}
