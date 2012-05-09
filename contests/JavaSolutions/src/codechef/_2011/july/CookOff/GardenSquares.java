package codechef._2011.july.CookOff;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.util.Locale;

public final class GardenSquares {

	static {
		final Locale us = Locale.US;
		if (!Locale.getDefault().equals(us)) {
			Locale.setDefault(us);
		}
	}

	static boolean file = false;
	static boolean isLocal = true;

	static BufferedReader in;
	static {
		try {
			// in = new Scanner(file ? new
			// FileInputStream("c:\\var\\tmp\\in.txt")
			// : System.in);

			in = new BufferedReader(new InputStreamReader(
					file ? new FileInputStream("c:\\var\\tmp\\in.txt")
							: System.in));

			// in = new StreamTokenizer(new BufferedReader(new
			// InputStreamReader(
			// file ? new FileInputStream("c:\\var\\tmp\\in.txt")
			// : System.in)));
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

	static PrintStream err;
	static {
		err = System.err;
	}

	/**
	 * @param args
	 * @throws IOException
	 */
	public static void main(final String[] args) throws IOException {

		final long startTime = System.nanoTime();
		final int t = Integer.parseInt(in.readLine());

		for (int i = 0; i < t; ++i) {
			solve(i + 1);
			if (isLocal && file) {
				err.println(i + 1 + "/" + t);
			}
			if (isLocal && !file) {
				out.flush();
			}
		}

		if (isLocal) {
			err.println(String.format("Completed after %d ms.",
					(System.nanoTime() - startTime) / 1000000));
		}

		out.flush();
		if (file) {
			out.close();
		}

	}

	private static void solve(final int testId) throws IOException {
		final String[] ss = in.readLine().split(" ");
		final int n = Integer.parseInt(ss[0]), m = Integer.parseInt(ss[1]);

		final String[] table = new String[n];
		for (int i = 0; i < n; ++i) {
			table[i] = in.readLine();
		}

		int ans = 0;

		for (int i = 0; i < n - 1; ++i) {
			for (int j = 0; j < m - 1; ++j) {
				for (int k = Math.min(n - i - 1, m - j - 1); k >= 1; --k) {
					final char c = table[i].charAt(j);
					if (table[i].charAt(j + k) == c
							&& table[i + k].charAt(j) == c
							&& table[i + k].charAt(j + k) == c) {
						++ans;
					}
				}
			}
		}

		out.println(ans);
	}
}
