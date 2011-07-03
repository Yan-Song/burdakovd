package gcj.year2011.qualification;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.io.StreamTokenizer;
import java.util.ArrayDeque;
import java.util.Deque;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Locale;
import java.util.Map;
import java.util.Set;

public final class B {

	static {
		final Locale us = Locale.US;
		if (!Locale.getDefault().equals(us)) {
			Locale.setDefault(us);
		}
	}

	static boolean file = true;
	static boolean isLocal = true;

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
		try {
			final long startTime = System.nanoTime();
			final int t = nextInt();
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
		} finally {
			out.flush();
			if (file) {
				out.close();
			}
		}
	}

	private static void solve(final int testId) throws IOException {
		final int c = nextInt();
		final Map<String, Character> combinations = new HashMap<String, Character>();
		for (int i = 0; i < c; ++i) {
			final String combination = nextWord();
			final String requisite = combination.substring(0, 2);
			final char result = combination.charAt(2);
			combinations.put(requisite, result);
			combinations.put(new StringBuilder(requisite).reverse().toString(),
					result);
		}

		final int d = nextInt();
		final Set<String> oppositions = new HashSet<String>();
		for (int i = 0; i < d; ++i) {
			final String opposition = nextWord();
			oppositions.add(opposition);
			oppositions.add(new StringBuilder(opposition).reverse().toString());
		}

		nextInt(); // n
		final String input = nextWord();

		final Deque<Character> stack = new ArrayDeque<Character>();
		for (final char current : input.toCharArray()) {
			if (stack.isEmpty()) {
				stack.push(current);
			} else {
				final String combination = "" + stack.getFirst() + current;
				if (combinations.containsKey(combination)) {
					stack.pop();
					stack.push(combinations.get(combination));
				} else {
					stack.push(current);
					for (final char old : stack) {
						final String opposition = "" + old + current;
						if (oppositions.contains(opposition)) {
							stack.clear();
							break;
						}
					}
				}
			}
		}

		out.printf("Case #%d: [", testId);
		boolean first = true;
		for (final Iterator<Character> it = stack.descendingIterator(); it
				.hasNext();) {
			if (!first) {
				out.print(", ");
			}
			first = false;
			out.print(it.next());
		}
		out.println("]");
	}
}
