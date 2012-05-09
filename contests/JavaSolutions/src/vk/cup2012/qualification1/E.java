package vk.cup2012.qualification1;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.io.StreamTokenizer;
import java.util.Arrays;
import java.util.Locale;

public class E {

	static {
		final Locale us = Locale.US;
		if (!Locale.getDefault().equals(us)) {
			Locale.setDefault(us);
		}
	}

	static boolean file = false;
	static boolean isLocal = false;

	private static int nextInt() throws IOException {
		in.nextToken();
		return (int) in.nval;
	}

	private static String nextWord() throws IOException {
		in.nextToken();
		return in.sval;
	}

	static StreamTokenizer in;
	static {
		try {
			// in = new Scanner(file ? new
			// FileInputStream("c:\\var\\tmp\\in.txt")
			// : System.in);

			// in = new BufferedReader(new InputStreamReader(
			// file ? new FileInputStream("c:\\var\\tmp\\in.txt")
			// : System.in));

			in = new StreamTokenizer(new BufferedReader(new InputStreamReader(
					file ? new FileInputStream("c:\\var\\tmp\\in.txt")
							: System.in)));
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
		final int t = 1;// nextInt();

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

	private static void Assert(final boolean x) {
		if (!x) {
			System.err.println("Assertion failed");
		}
	}

	private static void solve(final int testId) throws IOException {
		final int N = nextInt();
		final int K = nextInt();

		final int[] t = new int[N + 1];
		final int[] d = new int[N + 1];

		for (int i = 0; i < N; ++i) {
			t[i] = nextInt() - 1;
			d[i] = nextInt();
		}
		t[N] = 86400;

		// dp[i][j] - в какой момент времени можно закончить i звонков если
		// можно пропускать не более j раз
		final int[][] dp = new int[N + 1][K + 1];

		for (final int[] q : dp) {
			Arrays.fill(q, 1000000000);
		}

		Arrays.fill(dp[0], 0);

		for (int passed = 1; passed <= N; ++passed) {
			for (int skipped = 0; skipped <= K; ++skipped) {
				dp[passed][skipped] = Math.max(dp[passed - 1][skipped],
						t[passed - 1]) + d[passed - 1];
				if (skipped > 0) {
					dp[passed][skipped] = Math.min(dp[passed][skipped],
							dp[passed - 1][skipped - 1]);
				}
			}
		}

		int ans = 0;

		for (int after = 0; after <= N; ++after) {
			for (int skipBefore = 0; skipBefore <= K; ++skipBefore) {
				final int nextCall = t[Math.min(N, after + K - skipBefore)];
				ans = Math.max(ans, nextCall - dp[after][skipBefore]);
			}
		}

		out.println(ans);
	}
}
