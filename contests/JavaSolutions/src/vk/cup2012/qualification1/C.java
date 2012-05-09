package vk.cup2012.qualification1;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.util.Locale;
import java.util.Stack;

public class C {

	static {
		final Locale us = Locale.US;
		if (!Locale.getDefault().equals(us)) {
			Locale.setDefault(us);
		}
	}

	static boolean file = false;
	static boolean isLocal = false;

	private static int nextInt() throws IOException {
		return Integer.parseInt(nextLine());
	}

	private static String nextLine() throws IOException {
		return in.readLine();
	}

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
		final int n = nextInt();

		final Stack<String> wd = new Stack<String>();

		for (int i = 0; i < n; ++i) {
			final String[] command = nextLine().trim().split(" ");

			if (command[0].equals("cd")) {
				String path = command[1];
				if (path.startsWith("/")) {
					wd.clear();
					path = path.substring(1);
				}
				for (final String dir : path.split("/")) {
					if (dir.equals("..")) {
						wd.pop();
					} else {
						wd.push(dir);
					}
				}
			} else {
				final StringBuilder ans = new StringBuilder("/");
				for (final String dir : wd) {
					ans.append(dir);
					ans.append('/');
				}
				out.println(ans.toString());
			}
		}
	}
}
