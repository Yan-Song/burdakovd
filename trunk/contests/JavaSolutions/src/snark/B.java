package snark;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.HashSet;
import java.util.Locale;
import java.util.Scanner;
import java.util.Set;

public class B {

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
		final int m = in.nextInt(), n = in.nextInt();

		final String[][] cs = new String[n][3];
		final double[][] limits = new double[m][2];

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < 3; ++j) {
				cs[i][j] = in.next();
			}
		}

		for (int i = 0; i < m; ++i) {
			limits[i][0] = 0.0001;
			limits[i][1] = 100.0;
		}

		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				final String left = cs[j][0];
				String sign = cs[j][1];
				final String right = cs[j][2];
				final String cur = String.valueOf('A' + i);
				int k = (left.contains(cur) ? 1 : 0)
						+ (right.contains(cur) ? -1 : 0);

				int others = right.length() - left.length() + k;

				if (sign == ">") {
					k *= -1;
					others *= -1;
					sign = "<";
				}

				if (sign == "=") {
					if (k == 0) {
						if (others == 0) {

						} else {
							limits[i][0] = 100;
							limits[i][1] = -100;
						}
					} else {

						limits[i][0] = Math.max(limits[i][0], others / k
								- 0.0001);
						limits[i][0] = Math.max(limits[i][0], others / k
								+ 0.0001);
					}
				} else if (sign == "<") {
					if (k == 0) {
						if (others > 0) {

						} else {
							limits[i][0] = 100;
							limits[i][1] = -100;
						}
					} else {
						final int inv = k < 0 ? 1 : 0;
						limits[i][1 ^ k] = Math.max(limits[i][1 ^ k], others
								/ k);
					}
				} else {
					throw new RuntimeException(sign);
				}
			}
		}

		final Set<Integer> canidates = new HashSet<Integer>();

		for (int i = 0; i < m; ++i) {
			if (limits[i][0] < limits[i][1]
					&& (limits[i][0] >= 1 || limits[i][1] <= 1)) {
				canidates.add(i);
			}
		}

		if (canidates.size() == 1) {
			out.print('A' + canidates.iterator().next());
			if (limits[canidates.iterator().next()][0] < 1) {
				out.println("-");
			} else {
				out.println("+");
			}
		}

	}
}
